#include <random>
#include <iostream>
#include <string>

template <typename TDistribution>
double sample_mean(TDistribution dist, int sample_size = 10000)
{
    std::mt19937 mt; // Mersenne Twister generator
    double sum = 0;
    for (int i = 0; i < sample_size; ++i)
	sum += dist(mt);
    return sum / sample_size;
}

template <typename TDistribution>
void test_mean(TDistribution dist, std::string name, double true_mean, double true_variance)
{
    double true_stdev = sqrt(true_variance);
    std::cout << "Testing " << name << " distribution\n";
    int sample_size = 10000;
    double mean = sample_mean(dist, sample_size);
    std::cout << "Computed mean: " << mean << "\n";
    double lower = true_mean - true_stdev/sqrt((double)sample_size);
    double upper = true_mean + true_stdev/sqrt((double)sample_size);
    std::cout << "Expected a value between " << lower << " and " << upper << "\n\n";
}

int main()
{
    int n;
    double p, lambda, shape, mu, sigma;

    n = 5; p = 0.3;
    std::binomial_distribution<int> binomial(n, p);
    test_mean(binomial, "binomial", n*p, n*p*(1-p));

    lambda = 4.0;
    std::exponential_distribution<double> exponential(lambda);
    test_mean(exponential, "exponential", 1.0/lambda, 1.0/(lambda*lambda));

    shape = 3.0;
    std::gamma_distribution<double> gamma(shape);
    test_mean(gamma, "gamma", shape, shape);

    p = 0.1;
    std::geometric_distribution<int> geometric(p);
    test_mean(geometric, "geometric", 1.0/p, (1.0 - p)/(p*p));

    mu = 3.0; sigma = 4.0;
    std::normal_distribution<double> normal(mu, sigma);
    test_mean(normal, "normal", mu, sigma*sigma);

    lambda = 7.0;
    std::poisson_distribution<int> poisson(7.0);
    test_mean(poisson, "poisson", lambda, lambda);

    p = 0.6;
    std::bernoulli_distribution bernoulli(p);
    test_mean(bernoulli, "bernoulli", p, p*(1-p));

    return (0);
}
