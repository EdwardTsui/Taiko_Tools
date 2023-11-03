#pragma once

#include <string>

namespace Edward
{
	double rateToPpy(const double);
	double ppyToRate(const double);
};

class Circle
{
public:
	Circle(std::string);
	Circle();
	bool isDon() { return isdon; }
	bool isKat() { return !isdon; }
	bool isFinisher() { return isfinisher; }
	int getX() { return posx; }
	void setX(const int x) { posx = x; }
	int getY() { return posy; }
	void setY(const int y) { posy = y; }
	int getTimeStamp() { return timestamp; }
	void setTimeStamp(const int x) { timestamp = x; }
	int getNoteType() { return notetype; }
	void setNoteType(const int x) { notetype = x; }
	int getSound() { return sound; }
	void setSound(const int x) { sound = x; }
	std::string getLineSix() { return lsix; }
	void setLineSix(std::string x) { lsix = x; }
	void setDon();
	void setKat();
	void setFinisher();
	void unFinisher();
	std::string getString();
	virtual ~Circle() { };
private:
	int posx, posy;
	int timestamp;
	int notetype;
	bool isdon;
	bool isfinisher;
	int sound;
	std::string lsix;
};

class Line
{
public:
	Line(std::string);
	Line();
	virtual ~Line() { }
	int getTimeStamp() { return timestamp; }
	double getBPM() { return bpm; }
	void setBPM(const double x) { bpm = x; };
	void setRate(const double);
	void setLineType(const bool x) { isredline = x; }
	std::string getString();
	int getBeat() { return beat; }
	int getSoundSet() { return soundset; }
	int getSoundEffect() { return soundeffect; }
	int getVolume() { return volume; }
	bool isRed() { return isredline; }
	int getEffect() { return effect; }
private:
	int timestamp;
	double bpm;
	int beat;
	int soundset;
	int soundeffect;
	int volume;
	bool isredline;
	int effect;
};