FROM skylyrac/blocksds:slim-latest

RUN apt update && \
    apt install python3-full python3-pip ninja-build wget libxxf86vm1 libxfixes3 libxi6 libxkbcommon-x11-0 libsm6 libgl1 libopengl-dev unzip -y

RUN git clone https://github.com/AntonioND/architectds.git && \
    cd ./architectds && \
    pip3 install wheel setuptools --break-system-packages && \
    python3 setup.py bdist_wheel && \
    pip3 install dist/architectds-*-py3-none-any.whl --break-system-packages && \
    cd ../ && \
    rm -rf architectds

ENTRYPOINT [ "/bin/bash" ]