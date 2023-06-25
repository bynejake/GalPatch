#pragma once

class StringUtil final
{
public:
	template <typename T>
	static void EraseToLastOf(std::basic_string<T>& str, const T& pattern)
	{
		const auto pos = str.find_last_of(pattern);
		if (pos != std::string::npos)
			str.erase(0, pos + 1);
	}

	template <typename T>
	static BOOL StartsWith(const std::basic_string<T>& str, const std::vector<const T*>& patterns)
	{
		for (auto pattern : patterns)
		{
			if (str.starts_with(pattern))
				return TRUE;
		}
		return FALSE;
	}

	template <typename T>
	static BOOL Contains(const std::basic_string<T>& str, const std::vector<const T*>& patterns)
	{
		for (auto pattern : patterns)
		{
			if (str.contains(pattern))
				return TRUE;
		}
		return FALSE;
	}

	template <typename T>
	static BOOL EndsWith(const std::basic_string<T>& str, const std::vector<const T*>& patterns)
	{
		for (auto pattern : patterns)
		{
			if (str.ends_with(pattern))
				return TRUE;
		}
		return FALSE;
	}
};
