
Avant toute chose, si vous avez plusieurs versions de gcc/g++ installées sur votre système, pensez à définir les variables globales suivantes (dans votre .bashrc par exemple) :

export CC=path/to/gcc
export CXX=path/to/g++

Si ces variables sont définit, CMake utilisera les compilateurs indiqués.

La compilation se fait dans un dossier temporaire, à la racine du projet :
	mkdir build
	cd build

Compilation simple du projet complet :

	cmake ..
	make

par défaut en mode debuggage.

Compilation sans le mode débuggage :

	cmake .. -DRELEASE_MODE=yes
	make

Compilation avec la génération de la documentation (avec le mode de debuggage) :

	cmake .. -DDOC_MODE=YES
	make
Comme doxygen génère beaucoup de fichiers, je vous suggère de ne pas lancer cmake dans un environement de développement 

Compilation avec la documentation et sans le mode débuggage :

	cmake .. -DRELEASE_MODE=yes -DDOC_MODE=YES
	make

Pour spécifier un dossier d'installation de la lib :
	
	cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/usr -DRELEASE_MODE=yes -DDOC_MODE=YES
	make

Compilation avec la documentation, sans le mode débuggage, avec un préfix d'installation :

	cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/usr -DRELEASE_MODE=yes -DDOC_MODE=YES
	make
	make install
	
Vérifiez que vous avez bien les droits en écriture sur le dossier que vous définissez comme préfix d'installation.
