
#prerequiste
sudo apt-get update
sudo apt-get install --reinstall libxcb-xinerama0 \
	     cmake build-essential libgl1-mesa-dev \
	          libglu1-mesa-dev freeglut3-dev cmake

sudo apt install libxcb-cursor0 libxcb-cursor-dev

#download online installer and run

wget https://download.qt.io/archive/online_installers/4.5/qt-unified-linux-x64-4.5.2-online.run
chmod +x qt-unified-linux-x64-4.5.2-online.run
#./qt-unified-linux-x64-4.5.2-online.run --mirror https://mirrors.tuna.tsinghua.edu.cn/qt
./qt-unified-linux-x64-4.5.2-online.run
