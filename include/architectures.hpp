#pragma once

struct Architecture 
{ 
  enum Type {
    AVR,
    SAM,
    SAMD,
    unknown
  };
  
  Architecture(Type arch) : type(arch) {}

  bool operator==(const Type& other) const { return type == other; }

  Type type;
};

constexpr
Architecture::Type architecture()
{
  #if defined(ARDUINO_ARCH_AVR)
    return Architecture::AVR;
  #elif defined(ARDUINO_ARCH_SAM)
    return Architecture::SAM;
  #elif defined(ARDUINO_ARCH_SAMD)
    return Architecture::SAMD;
  #endif
}

constexpr
bool isArchitecture(Architecture::Type expected)
{
  return architecture() == expected;
}

String toString(Architecture::Type arch)
{
  switch(arch)
  {
    case Architecture::SAMD: return "SAMD";
    default: return "unkown";
  }
}

void printArchitecture()
{
  Serial.print("Architecture: ");
  Serial.println(toString(architecture()));
}

