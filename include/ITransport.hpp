#pragma once
#include <string>
#include <variant>

using TransportValue = std::variant<int, bool, double, std::string>;

class ITransport
{
public:
	virtual ~ITransport () = default;
	virtual bool send (const std::string& target, const TransportValue& val) = 0; 
};