#include "ulp-calc.h"

double ulp(int p, double x){
    if(x == 1){
        //ulp de 1
        return potencia(2, -(p-1)); //2^-(p-1)
    }else{
        
        return ulp(p, 1) * potencia(2, piso(log2(x)));
        //ulp(x) = ulp(1) * 2^(funçãoPiso(logx))    
    }
}
/**
Esta função cria um arquivo com um script que descreve os detalhes
da plotagem a ser feita e os dados para serem plotados no grafico.
No final ela chama o software gnuplot para criar o grafico baseado 
nestes dados.
*/
std::string exponentialGraph(int mant){
    //stream (fluxo) de dados para o arquivo do grafico
    std::ofstream graph;
    std::string archiveName = "output-" + std::to_string(mant) + "-1"; //esse numero no fim é importante para não sobrescrever outros graficos
    //o arquivo com o script e os dados terá a extensão ".data"
    graph.open(archiveName + ".data");
    
    //comando de plotagem para ser interpretado pelo software "gnuplot"
    std::string plotDeclaration = "set title \"" + std::to_string(mant) + " PRECISION ULP - GRAPH 1\"\n" +
        "set logscale x 2\n" +
        "set xrange[1:" + std::to_string(potencia(2, mant-1)) + "]\n" +
        "set xlabel \"x\"\n" +
        "set yrange[0:1]\n" +
        "set ylabel \"ULP(x)\"\n" +
        "set terminal pngcairo size 900,700 enhanced font 'Verdana,10'\n" +
        "set output \"" + archiveName + ".png\"\n" +
        "plot \"-\" using 1:2 title 'ULP(X)' with linespoints\n";
    graph << plotDeclaration;
    
    //insere os dados de ulp referentes as potencias de 2 no arquivo
    for (int i = 0; i <= mant - 1; i++) {
        float p = potencia(2, i);
        double ulpTemp = ulp(mant, p);
        graph << p << "\t" << ulpTemp << "\n";
    }
    //fecha o arquivo
    graph.close();
    
    //cria o comando para o prompt de comandos do sistema no formato "gnuplot arquivo.data"
    //e então manda para o sistema para que seja executado
    std::string plotCommand = "gnuplot " + archiveName + ".data";
    system(plotCommand.c_str());
    
    //retorna o nome do arquivo com os dados
    //isso não é tão importante, não está sendo utilizado no momento
    return archiveName + ".data";
}

/**
Mesma coisa que a função acima, porém ela não força o eixo X do grafico para que seja exponencial
se tornando assim uma função de primeiro grau (reta)
*/
std::string linearGraph(int mant){
    std::ofstream graph;
    std::string archiveName = "output-" + std::to_string(mant) + "-2";
    graph.open(archiveName + ".data");
    
    std::string plotDeclaration = "set title \"" + std::to_string(mant) + " PRECISION ULP - GRAPH 2\"\n" +
        "set xrange[1:" + std::to_string(potencia(2, mant-1)) + "]\n" +
        "set xlabel \"x\"\n" +
        "set yrange[0:1]\n" +
        "set ylabel \"ULP(x)\"\n" +
        "set terminal pngcairo size 900,700 enhanced font 'Verdana,10'\n" +
        "set output \"" + archiveName + ".png\"\n" +
        "plot \"-\" using 1:2 title 'ULP(X)' with linespoints\n";
    graph << plotDeclaration;
    
    for (int i = 0; i <= mant - 1; i++) {
        float p = potencia(2, i);
        double ulpTemp = ulp(mant, p);
        graph << p << "\t" << ulpTemp << "\n";
    }
    
    graph.close();
    std::string plotCommand = "gnuplot " + archiveName + ".data";
    system(plotCommand.c_str());
    
    return archiveName + ".data";
}

/**
Esta função cria um grafico com os valores de ulp não apenas para as potencias de 2.
por isso ela adquire a aparencia de "degraus".
*/
std::string trueGraph(int mant){
    //stream (fluxo) de dados para o arquivo do grafico
	std::ofstream graph;
    //esse numero "-3" no fim é importante para não sobrescrever outros graficos
    std::string archiveName = "output-" + std::to_string(mant) + "-3";
    //definie o valor maximo até onde serão calculados os ulps
    float maxValue = potencia(2, mant-1);
    //o arquivo com o script e os dados terá a extensão ".data"
    graph.open(archiveName + ".data");
    
    //comando de plotagem para ser interpretado pelo software "gnuplot"
    std::string plotDeclaration = "set title \"" + std::to_string(mant) + " PRECISION ULP - GRAPH 3\"\n" +
        "set xrange[1:" + std::to_string(maxValue) + "]\n" +
        "set xlabel \"x\"\n" +
        "set yrange[0:1]\n" +
        "set ylabel \"ULP(x)\"\n" +
        "set terminal pngcairo size 900,700 enhanced font 'Verdana,10'\n" +
        "set output \"" + archiveName + ".png\"\n" +
        "plot \"-\" using 1:2 title 'ULP(X)' with linespoints\n";
    graph << plotDeclaration;
    
    //ticks existe porque não podemos simplesmente testar todos os valores de x possiveis
    float ticks = maxValue / 10000; //o grafico terá 10000 "pontos"
    for (double i = 1; i <= maxValue; i+=ticks) {
        graph << i << "\t" << ulp(mant, i) << "\n";
    }
    
    //fecha arquivo
    graph.close();
    std::string plotCommand = "gnuplot " + archiveName + ".data";
    //converte a string plotCommand para char[] e passa para o prompt do sistema
    system(plotCommand.c_str());
    
    //retorna o nome do arquivo
    return archiveName + ".data";
}

/**
Esta função cria um grafico para mostrar a variação da precisão relativa
através dos diversos valores de x numa determinada precisão.
É uma função lenta e PESADA que pode criar arquivos enormes, sua demonstração não está incluida.
Desconsiderar ela.
*/
std::string relativePrecisionGraph(int mant){
	std::ofstream graph;
    std::string archiveName = "output-" + std::to_string(mant) + "-precision";
    float maxValue = potencia(2, mant-1);
    graph.open(archiveName + ".data");
    
    std::string plotDeclaration = "set title \"" + std::to_string(mant) + " PRECISION, RELATIVE PRECISION\"\n" +
    	"set logscale x 2\n" +
        "set xrange[1:" + std::to_string(potencia(2, mant-1)) + "]\n" +
        //"set xrange[1:" + std::to_string(maxValue) + "]\n" +
        "set xlabel \"x\"\n" +
        //"set yrange[0:1]\n" +
        "set ylabel \"ULP(x) \\ x\"\n" +
        "set terminal pngcairo size 900,700 enhanced font 'Verdana,10'\n" +
        "set output \"" + archiveName + ".png\"\n" +
        "plot \"-\" using 1:2 with lines\n";
    graph << plotDeclaration;
    
    float ticks = maxValue / 500000;
    for (double i = 1; i <= maxValue; i+=ticks) {
        graph << i << "\t" << ulp(mant, i) / i << "\n";
    }
    
    graph.close();
    std::string plotCommand = "gnuplot " + archiveName + ".data";
    system(plotCommand.c_str());
    
    return archiveName + ".data";
}