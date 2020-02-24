// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <units/physical/natural/constants.h>
#include <units/physical/si/energy.h>
#include <units/physical/si/momentum.h>
#include <units/physical/si/velocity.h>
#include <units/physical/si/constants.h>
#include <units/math.h>
#include <iostream>

namespace {

using namespace units;

Energy AUTO total_energy(Momentum AUTO p, Mass AUTO m, Velocity AUTO c)
{
  return sqrt(pow<2>(p * c) + pow<2>(m * pow<2>(c)));
}

void si_example()
{
  using namespace si;

  const Momentum AUTO p = 4.q_GeV / speed_of_light;
  const momentum<kilogram_metre_per_second> p_si = p;
  const Mass AUTO m = 3.q_GeV / pow<2>(speed_of_light);
  const mass<kilogram> m_si = m;
  const Velocity AUTO c = speed_of_light;
  const Energy AUTO E = total_energy(p, m, c);
  const energy<joule> E_si = total_energy(p_si, m_si, c);

  std::cout << "p = " << p << "\n"
            << "p_si = " << p_si << "\n"
            << "m = " << m << "\n"
            << "m_si = " << m_si << "\n"
            << "c = " << c << "\n"
            << "E = " << E << "\n"
            << "E_si = " << E_si << "\n"
            << "E_GeV = " << quantity_cast<gigaelectronvolt>(E_si) << "\n";
}

void natural_example()
{
  using namespace natural;

  const momentum<gigaelectronvolt> p(4);
  const mass<gigaelectronvolt> m(3);
  const Velocity AUTO c = speed_of_light;
  const Energy AUTO E = total_energy(p, m, c);

  std::cout << "\nNatural units:\n"
            << "p = " << p << "\n"
            << "m = " << m << "\n"
            << "c = " << c << "\n"
            << "E = " << E << "\n";
}

} // namespace

int main()
{
  try {
    si_example();
    natural_example();
  }
  catch (const std::exception& ex) {
    std::cerr << "Unhandled std exception caught: " << ex.what() << '\n';
  }
  catch (...) {
    std::cerr << "Unhandled unknown exception caught\n";
  }
}
