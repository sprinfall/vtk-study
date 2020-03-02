# vtk-study

VTK 笔记，示例。

VTK 下载：https://vtk.org/download/

可视化工具：ParaView (https://www.paraview.org/)

## VTK 编译安装 (Windows)

### 安装路径

编译 VTK 时，注意 `CMAKE_INSTALL_PREFIX` 这个变量不能用 Windows 的“反斜杠”指定安装路径，否则安装后的 `VTKConfig.cmake` 文件会有“字符 Escape”错误。

比如，`CMAKE_INSTALL_PREFIX = D:\lib\cmake_install_2017_64` 是不对的，要改成 `D:/lib/cmake_install_2017_64`。

### 动态库 VS 静态库

VTK 缺省编译为动态库（CMake 选项 `BUILD_SHARED_LIBS` 为 ON）。

动态库链接 (LINK) 快，但是程序发布时带一堆 DLL 还是挺麻烦的。所以，可以考虑开发时用动态库，发布时用静态库，比如在 Jenkins 那台 PC 上用静态链接。

### Debug & Release

缺省情况下，编译 VTK 得到的库文件，Debug 和 Release 版文件名相同。 这就导致执行 CMake INSTALL 时，无法同时安装 Debug 和 Release 两套库文件。

解决办法是设置 `CMAKE_DEBUG_POSTFIX` (需要在 CMake 界面上勾选 `Advanced` 选项才能找到这个变量)，比如设 `CMAKE_DEBUG_POSTFIX` 为 `d`，这样 Debug 
版的库文件就多了一个 `d` 后缀，比如 `vtkCommonCore-8.2d.lib`。

在你的项目的 CMake 中，仍然通过 CMake 寻找 VTK，不需做任何更改。你的项目在 Debug 编译时，链接的就是有 `d` 后缀的库，在 Release 编译时，链接的就是没有 `d` 后缀的库。

### Qt

用 CMake 配置 VTK 时，要勾选 `VTK_Group_Qt`。

为了让 VTK 找到 Qt，把 Qt 的安装目录（比如 `C:\Qt\5.9.8\msvc2013_64`）添加到 `CMAKE_PREFIX_PATH` 变量。（指定 `Qt5_DIR` 也可以）。

再次打开生成的 VTK.sln，多了如下一些项目：

- vtkGUISupportQt
- vtkGUISupportQtSQL
- vtkRenderingQt
- vtkViewsQt

另见：https://www.vtk.org/Wiki/VTK/Configure_and_Build#Qt5..2A

### Find VTK

然后，在你的项目中，要通过 CMake 找到 VTK，添加 `D:\lib\cmake_install_2017_64` 到 `CMAKE_PREFIX_PATH`  就可以了。

注意：

- `CMAKE_PREFIX_PATH` 类型为 `FILEPATH`，可以指定多个目录，以分号分隔；
- `CMAKE_PREFIX_PATH` 里的路径可以用 Windows 的反斜杠。

如果不用 `CMAKE_PREFIX_PATH`，也可以添加环境变量 `VTK_DIR`，指向 VTK 的安装路径，比如：

```
VTK_DIR = D:\lib\cmake_install_2017_64
```

这两种方法都可以使 CMake 通过 `find_package(VTK)` 找到 VTK。

### QVTKWidgetPlugin

为了让 Qt Designer 能够支持 VTK 的 QVTKWidget，需要把 QVTKWidgetPlugin.dll 拷贝到 Qt 安装目录里的 `plugins\designer` 目录。但是，这里有几个难点。

首先，QVTKWidgetPlugin.dll 只在 VTK 编译为动态库时才会生成，即在 CMake 里配置 VTK 时，需勾选 `BUILD_SHARED_LIBS`（缺省行为）。

其次，Qt Creator 一般为 32 位程序，QVTKWidgetPlugin.dll 也必须编译成 32 位的库。但是，很可能你想把 VTK 编译成 64 位，因为你的 Qt 可能也是 64 位。

最后，QVTKWidgetPlugin.dll 得是 RELEASE 版的才行。

## VTK 编译安装 (Linux)

下载[源代码](https://vtk.org/download/#latest)，当前版本为 8.2.0。

如果下载了测试数据，即  VTKData 或 VTKLargeData（[测试数据是干吗的？见此 Wiki](https://www.vtk.org/Wiki/VTK_Datasets)），请解压到 VTK 源代码目录，得到一个隐藏的子目录 `.ExternalData`。

### Dependencies

VTK 依赖于 OpenGL：

```
$ sudo apt install libgl-dev
```

实际安装的应该是 `libgl1-mesa-dev`。

还有 X11 相关的开发包：

```
$ sudo apt install libxt-dev
```

将同时安装 `libice-dev` 和 `libsm-dev`。

### CMake Configure Options

#### CMAKE_BUILD_TYPE

缺省为 Debug，开发环境中用  Debug 也是合理的。

#### BUILD_SHARED_LIBS

缺省为 ON，最好不要更改。

如果不想在软件发布时打包一堆动态库，就用静态库吧。但是开发环境仍然建议用动态库，发布环境用静态库就可以了。

**动态库安装（`sudo make install`）后，必须运行 `sudo ldconfig`，否则无法加载。**

#### BUILD_DOCUMENTATION

试过但是失败了。建议直接下载 [vtkDocHtml-8.2.0.tar.gz](https://www.vtk.org/files/release/8.2/vtkDocHtml-8.2.0.tar.gz)。

#### BUILD_EXAMPLES

建议勾选，VTK 的例子值得学习。

#### BUILD_TESTING

如果 VTKData 已经解压到子目录 `.ExternalData`，这个选项缺省就为 `ON`（有待确认）。 

注意 `.ExternalData/MD5` 里的文件与 `Testing/Data/` 里的 `*.md5` 的对应关系。

#### VTK_Group_Qt

把 Qt 的安装目录（比如 `/home/adam/Qt/5.13.1/gcc_64`）添加到 `CMAKE_PREFIX_PATH` 变量。在 CMake 界面上点 `Add Entry` 按钮，输入 Name 为 `CMAKE_PREFIX_PATH`，Type 为 `FILEPATH`。

如果不用 `CMAKE_PREFIX_PATH`，指定 `Qt5_DIR` 也是可以的。

关于 Qt，我并没有用系统自带的源（我的桌面甚至还是 KDE 呢），而是从 Qt 官网直接下载安装的，这样避免跟系统软件包耦合，也能及时用上最新版的 Qt。

### Build & Install

```
$ make -j4
$ sudo make install
```

安装文件的目录为 `/usr/local/include/vtk-8.2/`和 `/usr/local/lib/`。

如果在编译示例时失败了（ `BUILD_EXAMPLES` 为 ON），可以先设置 `BUILD_EXAMPLES` 为 OFF。

### Example Data

有些示例，特别是 Tcl 的示例，会用到 `VTK_DATA_ROOT` 指定的数据，这个数据可从下面链接下载： https://www.vtk.org/vtk-textbook-examples-and-data/

### Tcl 支持

设置 `VTK_WRAP_TCL` 为 ON。`VTK_Group_Tk`, `VTK_USE_TK` 这两个选项好像都不需要。

**安装 Tcl 和 tk 开发包：**

```
$ sudo apt install tcl-dev tk-dev
```

安装后，vtk 程序位于 `/usr/local/bin/vtk`。它依赖于很多 vtk 动态库，位于 `/usr/local/lib`，需要运行 `sudo ldconfig`，然后 vtk 程序才能正确加载这些动态库。

运行 `VTK-8.1.0/Examples/Tutorial/Step1/Tcl` 示例：

```
$ vtk Cone.tcl
```

如果编译 Examples 出错，可以临时把 `BUILD_EXAMPLES` 选项关掉。

**Tcl Deprecated?**

用 CMake 配置 VTK 8.1.1 时，警告如下：

> CMake Warning at CMakeLists.txt:477 (message):
>  Tcl wrapping support is deprecated as of VTK 8.1.
  
VTK 8.1.0 没有这个警告。
