#!/bin/bash

if [ ! -d build/ ]
then
        mkdir build
fi

cd build

cmake .. -DRELEASE_MODE=yes

make

#on lance le cas vectorisable
./Demonstration/DEMO_VECTORISABLE/demo_vectorisable > ../Demonstration/Results/demo_vectorisable.txt

#un cas avec une dépendance avant (vevtorisable)
./Demonstration/DEMO_FWD_DEPEND/demo_fwd_depend > ../Demonstration/Results/demo_fwd_depend.txt

#un cas avec une dépendance arrière (non-vevtorisable)
./Demonstration/DEMO_BACK_DEPEND/demo_back_depend > ../Demonstration/Results/demo_back_depend.txt



