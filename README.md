❏ O que  foi feito 
->Realce de Arestas
->Transformação da imagem colorida para tons de cinza;
->Aplicação do filtro gaussiano;
->Aplicaçaão do Filtro de Sobel;


❏ O que não foi feito :

❏ O que seria feito diferentemente :
A struct seria imagem, com cabeçario, e dentro dela outro tipo para os pixel, diferente do que fizemso sendo 2 structs totalmete separadas.

❏ Como compilar o projeto. Atenção, não será permitido o uso de bibliotecas externas.
gcc main.c ppm.c ppm.h -o catarata -lm
./catarata -i <inputfile> -f <formato (ex.:ppm)> -o <outputfile>

❏ Em caso de duplas:
○ Identificação dos autores;
RAMON DOMINGOS DUARTE OLIVEIRA
FÁBIO LEONARDO BRITO DE SOUSA

○ Contribuição de cada integrante no desenvolvimento do projeto 
->GetOpt- Ramon
->Leitura correta dos pixels da imamge,e armazenmaneto em matriz - Fabio;
->Transformação da imagem colorida para tons de cinza -  Ramon;
->Aplicação do filtro gaussiano - Ambos;
->Aplicaçaão do Filtro de Sobel - Fábio;

