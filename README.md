❏ O que  foi feito <br>
->Makefile
->Realce de Arestas<br>
->Transformação da imagem colorida para tons de cinza;<br>
->Aplicação do filtro gaussiano;<br>
->Aplicaçaão do Filtro de Sobel;<br>


❏ O que não foi feito :<br>

❏ O que seria feito diferentemente :<br>
A struct seria imagem, com cabeçario, e dentro dela outro tipo para os pixel, diferente do que fizemso sendo 2 structs totalmete separadas.

❏ Como compilar o projeto. <br>
gcc main.c ppm.c ppm.h -o catarata -lm<br>
./catarata -i <inputfile> -f <formato (ex.:ppm)> -o < outputfile > <br>

❏ Em caso de duplas:<br>
○ Identificação dos autores;<br>
RAMON DOMINGOS DUARTE OLIVEIRA <br>
FÁBIO LEONARDO BRITO DE SOUSA

○ Contribuição de cada integrante no desenvolvimento do projeto <br>
->GetOpt- Ramon<br>
->Leitura correta dos pixels da imamge,e armazenmaneto em matriz - Fabio;<br>
->Transformação da imagem colorida para tons de cinza -  Ramon;<br>
->Aplicação do filtro gaussiano - Ambos;<br>
->Aplicaçaão do Filtro de Sobel - Fábio;<br>
->makefile - Ramon
