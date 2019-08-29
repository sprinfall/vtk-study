# vtk-study

VTK 笔记，示例。

## VTK 的编译安装 (Windows)

编译 VTK 时，注意 `CMAKE_INSTALL_PREFIX` 这个变量不能用 Windows 的“反斜杠”指定安装路径，否则安装后的 `VTKConfig.cmake` 文件会有“字符 Escape”错误。

比如，`CMAKE_INSTALL_PREFIX = D:\lib\cmake_install_2017_64` 是不对的，要改成 `D:/lib/cmake_install_2017_64`。

然后，在你的项目中，要通过 CMake 找到 VTK，添加 `D:\lib\cmake_install_2017_64` 到 `CMAKE_PREFIX_PATH`  就可以了。

注意：

- `CMAKE_PREFIX_PATH` 类型为 `FILEPATH`，可以指定多个目录，以分号分隔；
- `CMAKE_PREFIX_PATH` 里的路径可以用 Windows 的反斜杠。

如果不用 `CMAKE_PREFIX_PATH`，也可以添加环境变量 `VTK_DIR`，指向 VTK 的安装路径，比如：

```
VTK_DIR = D:\lib\cmake_install_2017_64
```

这两种方法都可以使 CMake 通过 `find_package(VTK)` 找到 VTK。

## QVTKWidgetPlugin

为了让 Qt Designer 能够支持 VTK 的 QVTKWidget，需要把 QVTKWidgetPlugin.dll 拷贝到 Qt 安装目录里的 `plugins\designer` 目录。但是，这里有几个难点。

首先，QVTKWidgetPlugin.dll 只在 VTK 编译为动态库时才会生成，即在 CMake 里配置 VTK 时，需勾选 `BUILD_SHARED_LIBS`（缺省行为）。

其次，Qt Creator 一般为 32 位程序，QVTKWidgetPlugin.dll 也必须编译成 32 位的库。但是，很可能你想把 VTK 编译成 64 位，因为你的 Qt 可能也是 64 位。

最后，QVTKWidgetPlugin.dll 得是 RELEASE 版的才行。
