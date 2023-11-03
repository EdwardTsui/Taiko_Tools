#include "pch.h"
#include "Circle.h"

namespace Edward
{
	double rateToPpy(const double x)
	{
		double temp = x;
		temp = -100 / x;
		return temp;
	}
	double ppyToRate(const double x)
	{
		double temp = x;
		temp *= -1.0;
		temp = 100.0 / temp;
		return temp;
	}
}

Circle::Circle(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	std::string token, temp;
	posx = posy = timestamp = notetype = sound = 0;
	isdon = isfinisher = false;
	lsix = std::string("");
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		switch (k)
		{
		case 1:
			posx = std::stoi(token);
			break;
		case 2:
			posy = std::stoi(token);
			break;
		case 3:
			timestamp = std::stoi(token);
			break;
		case 4:
			notetype = std::stoi(token);
			break;
		case 5:
			sound = std::stoi(token);
			if (sound == 0)
			{
				isdon = true;
				isfinisher = false;
			}
			else if (sound == 2 || sound == 8 || sound == 10)
			{
				isdon = false;
				isfinisher = false;
			}
			else if (sound == 4)
			{
				isdon = true;
				isfinisher = true;
			}
			else if (sound == 6 || sound == 12 || sound == 14)
			{
				isdon = false;
				isfinisher = true;
			}
			else
			{
				isdon = false;
				isfinisher = false;
			}
			break;
		default:
			break;
		}
		parszline.erase(0, pos + delimiter.length());
	}
	lsix = parszline;
}

Circle::Circle()
{
	posx = posy = timestamp = notetype = sound = 0;
	isdon = isfinisher = false;
	lsix = std::string("");
}

void Circle::setDon()
{
	isdon = true;
	sound = 0;
}

void Circle::setKat()
{
	isdon = false;
	sound = 2;
}

void Circle::setFinisher()
{
	isfinisher = true;
	if (isdon)
	{
		sound = 4;
	}
	else
	{
		sound = 6;
	}
}

void Circle::unFinisher()
{
	isfinisher = false;
	if (isdon)
	{
		sound = 0;
	}
	else
	{
		sound = 2;
	}
}

std::string Circle::getString()
{
	std::string szline;
	szline += std::to_string(posx);
	szline += ",";
	szline += std::to_string(posy);
	szline += ",";
	szline += std::to_string(timestamp);
	szline += ",";
	szline += std::to_string(notetype);
	szline += ",";
	szline += std::to_string(sound);
	szline += ",";
	szline += lsix;
	return szline;
}

Line::Line(std::string parszline)
{
	std::string delimiter = ",";
	size_t pos = 0, k = 0;
	std::string token, temp;
	timestamp = beat = soundset = soundeffect = volume = isredline = bpm = beat = effect = 0;
	while ((pos = parszline.find(delimiter)) != -1)
	{
		k++;
		token = parszline.substr(0, pos);
		switch (k)
		{
		case 1:
			timestamp = std::stoi(token);
			break;
		case 2:
			bpm = std::stod(token);
			break;
		case 3:
			beat = std::stoi(token);
			break;
		case 4:
			soundset = std::stoi(token);
			break;
		case 5:
			soundeffect = std::stoi(token);
			break;
		case 6:
			volume = std::stoi(token);
			break;
		case 7:
			isredline = std::stoi(token);
			break;
		default:
			break;
		}
		parszline.erase(0, pos + delimiter.length());
	}
	effect = std::stoi(parszline);
}

Line::Line() 
{
	timestamp = beat = soundset = soundeffect = volume = isredline = bpm = beat = effect = 0;
}

std::string Line::getString()
{
	std::string szline;
	szline += std::to_string(timestamp);
	szline += ",";
	szline += std::to_string(bpm);
	szline += ",";
	szline += std::to_string(beat);
	szline += ",";
	szline += std::to_string(soundset);
	szline += ",";
	szline += std::to_string(soundeffect);
	szline += ",";
	szline += std::to_string(volume);
	szline += ",";
	szline += std::to_string(isredline);
	szline += ",";
	szline += std::to_string(effect);
	return szline;
}

void Line::setRate(const double x)
{
	double temp = Edward::ppyToRate(bpm);
	temp *= x;
	bpm = Edward::rateToPpy(temp);
}