#include <iostream>
#include <cmath>
#include <iomanip>

// Declaraciones
double fx(double t_k);
int findn(double solution, double left_limit, double right_limit);
double trapecio(int n, double left_limit, double right_limit, bool table);

int main()
{
    double wolfram = 0.9317044405;                   // Resultado Wolfram|Alpha
    double left_limit = 0.0;                         // Límite izquierdo
    double right_limit = 1.0;                        // Límite derecho
    int n = findn(wolfram, left_limit, right_limit); // Encontrar el n menor

    double delta_x = (right_limit - left_limit) / n; // Valor delta de x

    // Formato tabla
    std::cout << "\nn = " << n << "\t\t\tdelta_x = " << delta_x << "\n";
    std::cout << "f(x) = cos(x^3)\t\tIntervalo: [" << left_limit << "," << right_limit << "]\n\n";
    std::cout << "t_k\tx_k\t\tf(x_k)\n----\t------------\t------------\n";

    // Resultado
    double result = trapecio(n, left_limit, right_limit, true);
    std::cout << "\nMenor valor de n: " << n << "\n";
    std::cout << "Aproximación integral (con regla del trapecio):\n";
    std::cout << "\\int_0^1(cos(x^3)) = " << std::setprecision(10) << std::fixed << result << "\n\n";
    std::cout << "Valor Wolfram|Alpha: " << std::setprecision(10) << std::fixed << wolfram << "\n";
    std::cout << "Error en aproximación: " << std::abs(result - wolfram) << "\n\n";

    return 0;
}


// Función: f(x) = cos(x^3)
double fx(double tk)
{
    double tk3 = pow(tk, 3.0);
    double ft_k = cos(tk3);

    return ft_k;
}

// Encuentra el menor valor de n
int findn(double solution, double left_limit, double right_limit)
{
    double result = 0.0;
    double comparison = std::abs(solution - result); // Valor absoluto

    int n = 2;
    for (n; comparison > 1e-4; n++)      // Revisa que | T - W | < 10^{-4}
    {
        comparison = std::abs(solution - trapecio(n, left_limit, right_limit, false)); // Valor absoluto
        if (comparison <= 1e-4)
        {
            break;
        }
    }

    return n;
}

// Cálcula la integral con la regla del trapecio
double trapecio(int n, double left_limit, double right_limit, bool table)
{
    double sum = 0.0;
    double tk = left_limit;
    double delta_x = (right_limit - left_limit) / n;

    for (int jj = 0; jj <= n; jj++)
    {
        if (table)      // Para inprimir la tabla
        {
            std::cout << "t_" << jj << "\t";
            std::cout << std::setprecision(10) << std::fixed << tk << "\t";
            std::cout << std::setprecision(10) << std::fixed << fx(tk) << "\n";
        }

        sum += 2 * fx(tk);
        tk += delta_x;
    }

    // Aplicar regla del trapecio
    double result = (delta_x / 2) * (sum - fx(left_limit) - fx(right_limit));

    return result;
}