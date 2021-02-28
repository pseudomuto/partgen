#pragma once

#include <string>

namespace partgen {
class Part {
 public:
  /**
   * Creates a new Part.
   * @param name the name of the part (e.g <component>.<body>)
   * @param length the length in cm
   * @param width the width in cm
   * @param thickness the thickness in cm
   */
  Part(const std::string_view& name, double length, double width, double thickness)
      : name_(name), length_(length), width_(width), thickness_(thickness) {}

  std::string name() const { return name_; }
  double length() const { return length_; }
  double width() const { return width_; }
  double thickness() const { return thickness_; }

 private:
  std::string name_;
  double length_;
  double width_;
  double thickness_;
};
}  // namespace partgen
