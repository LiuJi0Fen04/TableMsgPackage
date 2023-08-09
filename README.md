# TableMsgPackage

this is a template help to build up a package via cmake


适应的工程结构
1. 项目刚刚开发，目前仅仅适用于当前文件结构

├── build           store binary files
├── include         without sub-folders
├── src             without sub-folders
├── autoMake.sh     do not change
├── CMakeLists.txt  write cmake in this form
├── install.sh      do not change
└── License.txt     license



安装
1. 首先运行automake，在build中生成相应的安装包
2. 再复制install.sh和相应的 $project-$platform.sh、$project-$platform.tar.gz到想要安装的文件夹，运行install即可安装
