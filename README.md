## 目的

Minor modifies for OS X compiling and MaciASL's OutlineView issue.

为在OS X下编译 acpi tools 和 MaciASL 的OutlineView显示问题，进行轻微的修改。

## 修改
#### Credit to RehabMan: [https://github.com/RehabMan/Intel-iasl](http://example.com)
###一、/generate/unix/Makefile.config (修改编译配置)

##### 1.1 在 37 行左右

```
HOST ?= _CYGWIN
```
修改为
```
HOST ?= _APPLE
```
---

##### 1.2 在 68行 和 69行 之间

```
INSTALLFLAGS ?= -f

else
```
添加
```
INSTALLFLAGS ?= -f

LDFLAGS = -mmacosx-version-min=10.6

else
```
#### 1.3 172行左右
删除
```
-Werror\
```
#### 1.4 194行左右
删除
```
-Woverride-init\
```

---

###二、disassembler
####2.1 /source/components/disassembler/dmbuffer.c
#### 2.1.1 223行左右

```
UINT8                   BufChar;
```
注释
```
/*    UINT8                   BufChar; */
```
#### 2.1.2 269行左右
```
AcpiOsPrintf ("  /* ");
for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
{
```
之前添加
```
#if 0
AcpiOsPrintf ("  /* ");
for (j = 0; j < ACPI_BUFFER_BYTES_PER_LINE; j++)
{
```
#### 2.1.3 292行左右
```
/* Finished with this line */

 AcpiOsPrintf (" */\n");
```
之后添加
```
/* Finished with this line */

AcpiOsPrintf (" */\n");
#else
AcpiOsPrintf ("\n");
#endif
```
#### 2.1.4 657行左右
```
ACPI_NAMESPACE_NODE     *Node;
ACPI_PARSE_OBJECT       *SizeOp;
ACPI_PARSE_OBJECT       *ParentOp;

/* Buffer size is the buffer argument */
```
之间添加
```
ACPI_NAMESPACE_NODE     *Node;
ACPI_PARSE_OBJECT       *SizeOp;
ACPI_PARSE_OBJECT       *ParentOp;
    
return 0;

/* Buffer size is the buffer argument */
```
#### 2.1.5 1089行左右
```
char                    IdBuffer[ACPI_EISAID_STRING_SIZE];
const AH_DEVICE_ID      *Info;

/* Convert EISAID to a string an emit the statement */
```
之间添加
```
char                    IdBuffer[ACPI_EISAID_STRING_SIZE];
#if 0
const AH_DEVICE_ID      *Info;
#endif

/* Convert EISAID to a string an emit the statement */
```
#### 2.1.6 1099行左右
```
/* If we know about the ID, emit the description */

Info = AcpiAhMatchHardwareId (IdBuffer);
if (Info)
{
    AcpiOsPrintf (" /* %s */", Info->Description);
}
}
```
添加
```
/* If we know about the ID, emit the description */
#if 0
Info = AcpiAhMatchHardwareId (IdBuffer);
if (Info)
{
    AcpiOsPrintf (" /* %s */", Info->Description);
}
#endif
}
```

---

### 2.2 /source/components/disassembler/dmopcode.c
#### 2.2.1 206行左右
```
if (!PrevOp->Asl.Node)
{
    AcpiOsPrintf (" /* External reference */");
    return;
}
```
添加
```
if (!PrevOp->Asl.Node)
{
#if 0
    AcpiOsPrintf (" /* External reference */");
#endif
    return;
}
```
#### 2.2.2 219行左右
```
/* Now: we can get the full pathname */

Pathname = AcpiNsGetExternalPathname (PrevOp->Asl.Node);
if (!Pathname)
{
    return;
}

AcpiOsPrintf (" /* %s */", Pathname);
ACPI_FREE (Pathname);
}
```
添加
```
/* Now: we can get the full pathname */
#if 0
Pathname = AcpiNsGetExternalPathname (PrevOp->Asl.Node);
if (!Pathname)
{
    return;
}

AcpiOsPrintf (" /* %s */", Pathname);
ACPI_FREE (Pathname);
#endif
}
```
#### 2.2.3 286行左右
```
}

AcpiOsPrintf (" // %s", AcpiUtGetNotifyName (NotifyValue, Type));
}
```
添加
```
}
#if 0
    AcpiOsPrintf (" // %s", AcpiUtGetNotifyName (NotifyValue, Type));
#endif
}
```
#### 2.2.4 864行左右
```
/* If we know about the ID, emit the description */

IdInfo = AcpiAhMatchHardwareId (Op->Common.Value.String);
if (IdInfo)
{
    AcpiOsPrintf (" /* %s */", IdInfo->Description);
}
}
    break;
```
添加
```
/* If we know about the ID, emit the description */
#if 0
IdInfo = AcpiAhMatchHardwareId (Op->Common.Value.String);
if (IdInfo)
{
    AcpiOsPrintf (" /* %s */", IdInfo->Description);
}
#endif
}
    break;
```

### 三、怎样编译
1. 在OS X下，先安装好 Xcode Command Line Tools.
2. 打开 终端，依次输入

2.1
```
cd Desktop
```
2.2
```
git clone https://github.com/Yuki-Judai/acpica.git
```
2.3
```
cd acpica
```
2.4
```
make
```
2.5

 编译好的文件在 /generate/unix/bin/ 目录。

### 四、编译版下载

[https://github.com/Yuki-Judai/acpica/releases](http://example.com)