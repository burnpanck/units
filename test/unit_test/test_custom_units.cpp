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

#include <units/dimensions/voltage.h>
#include <units/dimensions/frequency.h>
#include <units/math.h>

/* ************** DERIVED DIMENSIONS THAT INCLUDE UNITS WITH SPECIAL NAMES **************** */

namespace {

  struct base_dim_digital_information { static constexpr const char* value = "digital information"; };

  struct digital_information : units::make_dimension_t<units::exp<base_dim_digital_information, 1>> {};

  template<typename T>
  concept bool DigitalInformation = units::QuantityOf<T, digital_information>;

  struct bit : units::unit<digital_information> {};
  struct byte : units::unit<digital_information, units::ratio<8>> {};

  inline namespace literals {

    constexpr auto operator""_b(unsigned long long l) { return units::quantity<bit, std::int64_t>(l); }
    constexpr auto operator""_b(long double l) { return units::quantity<bit, long double>(l); }

    constexpr auto operator""_B(unsigned long long l) { return units::quantity<byte, std::int64_t>(l); }
    constexpr auto operator""_B(long double l) { return units::quantity<byte, long double>(l); }

  }
}

template<> struct units::downcast_traits<units::downcast_base_t<digital_information>> : std::type_identity<digital_information> {};
template<> struct units::downcast_traits<units::downcast_base_t<bit>> : std::type_identity<bit> {};
template<> struct units::downcast_traits<units::downcast_base_t<::byte>> : std::type_identity<::byte> {};

namespace {

  static_assert(1_B == 8_b);

}

namespace {

  using namespace units;

  // power spectral density
  struct power_spectral_density : make_dimension_t<units::exp<voltage, 2>, units::exp<frequency, -1>> {};
  struct sq_volt_per_hertz : unit<power_spectral_density> {};

  // amplitude spectral density
  struct amplitude_spectral_density : make_dimension_t<units::exp<voltage, 1>, units::exp<frequency, -1, 2>> {};
  // todo: add support for derived_unit
  //struct volt_per_sq_hertz : derived_unit<amplitude_spectral_density, kilogram, metre, second, ampere> {};
  struct volt_per_sqrt_hertz : unit<amplitude_spectral_density> {};
}

namespace units {

template<> struct downcast_traits<downcast_base_t<power_spectral_density>> : std::type_identity<power_spectral_density> {};
template<> struct downcast_traits<downcast_base_t<sq_volt_per_hertz>> : std::type_identity<sq_volt_per_hertz> {};

template<> struct downcast_traits<downcast_base_t<amplitude_spectral_density>> : std::type_identity<amplitude_spectral_density> {};
template<> struct downcast_traits<downcast_base_t<volt_per_sqrt_hertz>> : std::type_identity<volt_per_sqrt_hertz> {};

}

namespace {

  static_assert(std::is_same_v<dimension_sqrt_t<power_spectral_density>, amplitude_spectral_density>);
  static_assert(std::is_same_v<dimension_pow_t<amplitude_spectral_density, 2>, power_spectral_density>);

  static_assert(std::is_same_v<decltype(pow<2>(quantity<volt_per_sqrt_hertz>(4))), decltype(quantity<sq_volt_per_hertz>(16))>);
  static_assert(std::is_same_v<decltype(sqrt(quantity<sq_volt_per_hertz>(16))), decltype(quantity<volt_per_sqrt_hertz>(4))>);

}
