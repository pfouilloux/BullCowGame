#pragma once

#include <memory>
#include <stdexcept>

template <typename T> 
struct Nullable
{
public:
	Nullable() : Value(), IsSet(false) {}
	explicit Nullable(T Val) : Value(Val), IsSet(true) {}
	Nullable(const Nullable& Other) = default;

	friend void Swap(Nullable& A, Nullable& B)
	{
		std::swap(A.IsSet, B.IsSet);
		std::swap(A.Value, B.Value);
	}

	Nullable& operator=(Nullable Other)
	{
		Swap(*this, Other);
		return *this;
	}

	T operator=(T Val) { Set(Val); return Value; }
	bool operator==(T Val) { return IsSet && Val == Value; }
	explicit operator T() const { return Get(); }

	bool HasValue() const { return IsSet; }

	T Get() const
	{
		if(!IsSet)
		{
			throw std::logic_error("Value of Nullable was not set.");
		}

		return Value;
	}

	void Reset()
	{
		IsSet = false;
		Value = T();
	}
private:
	void Set(T Val)
	{
		Value = Val;
		IsSet = true;
	}
private:
	T Value;
	bool IsSet;
};
