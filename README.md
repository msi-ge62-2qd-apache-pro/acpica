## 目的
Minor modifies for OS X compiling and MaciASL.

为在OS X下编译 acpi tools 和 MaciASL 的显示问题，进行轻微的修改。

## 修改
### /generate/unix/Makefile.config (修改编译配置)
#### 在 37 行左右
> HOST ?= _CYGWIN

修改为

> HOST ?= _APPLE

#### 在 68行 和 69行 之间
> INSTALLFLAGS ?= -f

> else

添加
> INSTALLFLAGS ?= -f

> LDFLAGS = -mmacosx-version-min=10.6

> else

# 待更新......