## purpose
Minor modifies for OS X compiling and MaciASL.
为在OS X下编译 acpi tools 和 MaciASL 的显示问题，进行轻微的修改。

## Modifies
### /generate/unix/Makefile.config (for compiling in OS X)
#### around line 37
> HOST ?= _CYGWIN
修改
> HOST ?= _APPLE
#### between line 68 and 69
> INSTALLFLAGS ?= -f
> else
添加
> INSTALLFLAGS ?= -f
> LDFLAGS = -mmacosx-version-min=10.6
> else

待更新......