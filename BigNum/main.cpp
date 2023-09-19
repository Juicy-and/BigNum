#include <iostream>
#include <string>

class Big_integer {
private:
	std::string data;
public:
	Big_integer(std::string s) 
	{ 
		data = s; 
	}

	Big_integer& operator=(const Big_integer&& other) noexcept // оператор перемещающего присваивания
	{
		for (auto& i : other.data)
			data[i] = other.data[i];
		return *this;
	}

	Big_integer(Big_integer&& other) noexcept // конструктор перемещения
	{
		data = std::move(other.data);
	}

	Big_integer operator + (const Big_integer& other) const
	{
		std::string data_temp = data;
		std::string data_other = other.data;
		std::string temp{};
		int s,s1 = 0;
		while (!data_temp.empty() && !data_other.empty())
		{
			s = (data_temp.back() - 48) + (data_other.back() - 48) + s1;
			if (s >= 10)
			{
				s1 = s / 10;
				s = s % 10;
			}
			else s1 = 0;
			temp = char(s + 48) + temp;
			data_temp.erase(data_temp.size() - 1);
			data_other.erase(data_other.size() - 1);
		}
		if (data_temp.size())
			temp = data_temp + temp;
		else if (data_other.size())
			temp = data_other + temp;
		return Big_integer(temp);
	}
	friend std::ostream& operator << (std::ostream& os, const Big_integer& data)
	{
		return os << data.data;
	}

	Big_integer operator * (const int& mp) const
	{
		std::string data_temp = data;
		std::string temp{};
		int s, s1 = 0;
		int mp1 = mp;
		while (!data_temp.empty())
		{
			s = ((data_temp.back() - 48) * mp1) + s1;
			if (s >= 10)
			{
				s1 = s / 10;
				s = s % 10;
			}
			else s1 = 0;
			temp = char(s + 48) + temp;
			data_temp.erase(data_temp.size() - 1);
		}
		return Big_integer(temp);
	}
};

int main() {
	auto number1 = Big_integer("114575");
	auto number2 = Big_integer("78524");
	auto result = number1 + number2;
	auto result2 = number1 * 2;
	std::cout << result<< std::endl; // 193099
	std::cout << result2<<std::endl; // 229150
	return 0;
}
