#!/bin/bash

if [ ! -d build/ ]
then
        mkdir build
fi

cd build

# CC=$HOME/usr/bin/gcc CXX=$HOME/usr/bin/g++ cmake .. -DRELEASE_MODE=yes
CC=$HOME/usr/bin/gcc CXX=$HOME/usr/bin/g++ cmake .. -DRELEASE_MODE=no

make

#on lance le cas vectorisable
./Demonstration/DEMO_VECTORISABLE/demo_vectorisable > ../Demonstration/Results/demo_vectorisable.txt

#un cas avec une dépendance avant (vevtorisable)
./Demonstration/DEMO_FWD_DEPEND/demo_fwd_depend > ../Demonstration/Results/demo_fwd_depend.txt

#un cas avec une dépendance arrière (non-vevtorisable)
./Demonstration/DEMO_BACK_DEPEND/demo_back_depend > ../Demonstration/Results/demo_back_depend.txt

#on lance le cas vectorisable avec un nid de boucle
./Demonstration/DEMO_NID_DE_BOUCLE/demo_nid_de_boucle > ../Demonstration/Results/demo_nid_de_boucle.txt

#on vire les fichiers du dossier build
rm -fr *

