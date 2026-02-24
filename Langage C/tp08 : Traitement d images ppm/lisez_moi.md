# TP08 - Traitement d'images PPM

## Project description

This project is in 2 part :   
The first one can be execute with ./prog.bin you have an access to a menu with fonctionnalities. This functionnalities permet to load an image an create a new version in an oteher dimension binary or ascii of the image load.    
The second one can be execut with ./prog2.bin and you can execute by following the next indication some filtrage on your images.
But be carefull i dont understand why but my programm has an issue he doesn t execute the command directly  he execute a command after the next command have been excuted or after that you leave by typing quit. So you may have to execute twice the same instruction or other instructon to visualize the previous one. 

### 1. Seuillage
Execute with : seuillage value input_img output_img x_min y_min x_max y_max    

This function remplace pixel by black pixel if the average value of RGB is under a value. The value is choose by the user. The 3 coefficient before RGB are a pourcentages of what an human distinct of R and G and B.

### 2. Gradient  
Execute with : gradient input_img output_img x_min y_min x_max y_max  

The gradient made the image gray. I have calculed horizontal and verticl gradient with subject formule and after the norme. 

### 3. Lissage
Execute with : lissage input_img output_img x_min y_min x_max y_max  

The lissage made a convolution with matrice 3*3 and calculate the average of the 9 pixels and after we divided by 9. It create an image with more blur.