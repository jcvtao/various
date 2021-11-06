/*
 * Código para solucionar los ejercicios de práctica en la presentación
 * y programa en general para calcular integrales por medio de la regla
 * del trapectio y la regla de Simpson para n subintervalos definidos por el usuario.
*/

#include <iostream>
#include <cmath>
#include <iomanip>

// Declaraciones
using fptr = double(double);
// Funciones a integrar
double fx1(double t_k);
double fx2(double t_k);
double fx3(double t_k);
double fx4(double t_k);
// Funciones de las reglas
double simpson(int n, fptr function, double left_limit, double right_limit);
double trapecio(int n, fptr function, double left_limit, double right_limit);
// Función general
template <typename typealg>
double integral(int n, fptr function, typealg rule, double left_limit, double right_limit);

double pi = 2*acos(0.0); // Valor de Pi

int main()
{
    int n = 20;               // Número de subintervalos
    double left_limit = - pi;  // Límite izquierdo
    double right_limit = pi; // Límite derecho
    /* -------------------------------------------------------------------------*/

    double delta_x = (right_limit - left_limit) / n; // Valor delta de x

    // Formato tabla
    std::cout << "\nn = " << n << "\t\t\tdelta_x = " << delta_x
              << "\tIntervalo: [" << left_limit << "," << right_limit << "]\n\n";
    std::cout << "t_k\tx_k\t\tf(x_k)\n----\t------------\t------------\n";

    // Resultados
    double result1 = integral(n, fx4, trapecio, left_limit, right_limit); // Editar fx !
    double result2 = integral(n, fx4, simpson, left_limit, right_limit);  // Editar fx !
    std::cout << "\nAproximación integral (con regla del trapecio):\t" << result1 << "\n";
    std::cout << "Aproximación integral (con regla de Simpson):\t" << result2 << "\n\n";

    return 0;
}

// Funciones a integrar
double fx1(double tk)           // cos(t)
{
    double ft_k = cos(tk);
    return ft_k;
}
double fx2(double tk)           //t^2 + 2
{
    double tk3 = pow(tk, 2.0);
    double ft_k = tk3 + 2.0;
    return ft_k;
}
double fx3(double tk)           // 4x^3 - 1
{
    double tk3 = pow(tk, 3.0);
    double ft_k = (4 * tk3) - 1;
    return ft_k;
}
double fx4(double tk)           // 3 cos(t) / (2 + sin(t))^2
{
    double ft_k = (3 * cos(tk)) / (pow((2 + sin(tk)),2.0));
    return ft_k;
}

// Cálcula la integral con la regla de Simpson
double simpson(int n, fptr function, double left_limit, double right_limit)
{
    double sum = 0.0;
    double tk = left_limit;
    double delta_x = (right_limit - left_limit) / n;

    for (int jj = 0; jj <= n; jj++)
    {
        std::cout << "t_" << jj << "\t";
        std::cout << std::setprecision(10) << std::fixed << tk << "\t";
        std::cout << std::setprecision(10) << std::fixed << function(tk) << "\n";

        if (jj % 2 == 0)
        {
            sum += 2 * function(tk);
        }
        else
        {
            sum += 4 * function(tk);
        }

        tk += delta_x;
    }

    // Aplicar regla del Simpson
    double result = (delta_x / 3) * (sum - function(left_limit) - function(right_limit));

    return result;
}

// Cálcula la integral con la regla del trapecio
double trapecio(int n, fptr function, double left_limit, double right_limit)
{
    double sum = 0.0;
    double tk = left_limit;
    double delta_x = (right_limit - left_limit) / n;

    for (int jj = 0; jj <= n; jj++)
    {
        /*
        std::cout << "t_" << jj << "\t";
        std::cout << std::setprecision(10) << std::fixed << tk << "\t";
        std::cout << std::setprecision(10) << std::fixed << function(tk) << "\n";
        */

        sum += 2 * function(tk);
        tk += delta_x;
    }

    // Aplicar regla del trapecio
    double result = (delta_x / 2) * (sum - function(left_limit) - function(right_limit));

    return result;
}

// Función general
template <typename typealg>
double integral(int n, fptr function, typealg rule, double left_limit, double right_limit)
{
    double result = rule(n, function, left_limit, right_limit);
    return result;
}