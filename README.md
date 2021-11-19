

# APMI - Intérprete Matemático
## Como compilar e executar?
Para compilar o código basta con executar a orde `make` e executar o ficheiro executable xerado

    make
    ./bin/apmi

## Comandos dispoñibles:
A continuación mostrase unha pequena lista dos comandos que se permiten executar no  intérprete 

    clear()                 Borra as variables do espazo de traballo
    cls()                   Limpia a pantalla
    echo("on"/"off")        Activa ou desactiva o imprimir por pantalla
    exit()                  Cerra a terminal (alias quit())
    getwd()                 Obter o directorio de traballo actual
    help()                  Mostra esta axuda
    import("libreria")      Carga unha liberia externa, recibe como argumento a ruta da libreria
    libs()                  Mostra as librerías cargadas
    load("script")          Carga unha script matemático
    setwd("dir")            Cambiar directorio de traballo actual
    outmode("sci"/"dec")    Formato da salida: sci->formato cientifico;dec-> formato decimal
    print()                 Imprime un string
    quit()                  Cerra a terminal (alias exit())
    workspace()             Mostra as variables do espazo de traballo
Funcións matemáticas dispoñibles:

    acos(x)                 Arco coseno
    asin(x)                 Arco seno
    atan(x)                 Arco tanxente
    sin(x)                  Seno
    sinh(x)                 Seno hiperbólico
    cos(x)                  Coseno
    cosh(x)                 Coseno hiperbólico
    tan(x)                  Tanxente
    tanh(x)                 Tanxente hiperbólica
    log(x)                  Logaritmo
    log10(x)                Logaritmo en base 10
    exp(x)                  e^x
    abs(x)                  Valor absoluto
    floor(x)                Redondear hacia abaixo
    ceil(x)                 Redondear hacia arriba
    sqrt(x)                 Raiz cuadrada

## Constantes dispoñibles:
    pi                      Número PI:3.14159
    e                       Número e:2.7182
    aur                     Número aureo:1.6180
## Operacións matemáticas dispoñibles:

      a+b				Suma    
      a-b				Resta 		 
      a*b 				Multiplicación
      a/b				División
      a%b				Módulo
      a^b               Potencia
      (a)               Parentesis
      a=b               Asignación
      a[+ - * / %]=b    Asignación con operador

## Funcionalidade xeral

- O intérprete asume calquer identificador como variable ainda que non esté definido, e decir se empregamos a variable `foo` no intérprete sen previamente definila, asumirase que dita variable ten o valor 0.0.
- O intérprete asume calquer número introducido como un número decimal.

## Carga de ficheiros
Para cargar arquivos podemos empregar a función `load("ficheiro")`, pasando como argumento o ficheiro que queremos abrir, podendo cargar ata 10 ficheiros de maneira recursiva. Podemos empregar a función `setwd("directorio")` para cambiar de directorio de traballo, o establecer unha ruta absoluta ou relativo o directorio de traballo da terminal.

Adicionalmente o programa permite a carga de ficheiros por argumento, establecendo despois do executable o nome do arquivo que queremos executar:

    ./bin/apmi script.pa

## Uso de librerías
Para importar unha librería empregase a función `import("ficheiro")`.
A función import recibe como argumento un ficheiro compilado en C, esta ruta pode ser relativa ou absoluta o directorio de traballo, podese modificar o directorio de traballo empregando a sentencia `setwd("directorio")`.

Non se dispón de ningún límite de carga de librerías, as librerías cargadas podense consultar empregando a sentencia `libs()` no intérprete e borrar borrando o espazo de traballo con `clear()`.

As funcións definidas no arquivo importado deben recibir como argumento un único parámetro *double* e devolver un tipo *double*, outro tipo de funcións no están permitidas no intérprete.

Mencionar que non é posible executar unha función dunha librería que teña o mesmo o mesmo nome que unha constante/función ou unha variable da táboa de símbolos. Sempre prevalecerán os símbolos que a existen respecto os novos.

## Conxunto de exemplos 
Na carpeta `examples` atopase un exemplo, no cal se mostra un pouco as funcionalidades implementadas no programa. A súas funcionalidade está comentadas nos propios ficheiros e imprense addicionalmente mensaxes en pantalla coa función `print()` de cor azul.

Este exemplo poñera a proba o uso de un par de liberías(cuxo código tamén se pode consultar nesta carpeta), e o uso de gran parte dos comandos implementados no intérprete.

Para executar este exemplo temos dúas opcións:

#### Dende a propia terminal: 

    ./bin/apmi ./examples/exemplo.pa

#### Dende o intérprete empregando a función load()

     apmi> load("./examples/exemplo.pa") 

Notar que é importante que o directorio de traballo da terminal sexa o directorio do proxecto xa que dentro do propio script mostrase como funciona os comandos de cambio de directorio de traballo e carga de ficheiros.
