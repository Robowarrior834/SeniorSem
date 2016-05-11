#include <iostream>
#include "portaudio.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

/*
	This program is capable of generating and playing Morse code up to 26 words per minute.  Anything after that range will not funciton properly.
	Some of the code has been adapted from the sample Portaudio program.

*/

#define SAMPLE_RATE (88200)
#define TABLE_SIZE   (250)
#undef max

using namespace std;



typedef struct
{
	float sine[TABLE_SIZE];
	int left_phase;
	int right_phase;
	char message[20];
}
paTestData;


static int patestCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned long i;

	(void)timeInfo; /* Prevent unused variable warnings. */
	(void)statusFlags;
	(void)inputBuffer;

	for (i = 0; i<framesPerBuffer; i++)
	{
		*out++ = data->sine[data->left_phase];  /* left */
		*out++ = data->sine[data->right_phase];  /* right */
		data->left_phase += 1;
		if (data->left_phase >= TABLE_SIZE) data->left_phase -= TABLE_SIZE;
		data->right_phase += 2; /* higher pitch so we can distinguish left and right. */
		if (data->right_phase >= TABLE_SIZE) data->right_phase -= TABLE_SIZE;
	}

	return paContinue;
}



void tone(float unit) {//unit in seconds
	PaError err;
	PaStream *stream;
	int temp = 0;
	static paTestData data;
	int unitmili = 0; // unit in miliseconds
	unitmili = unit * 1000;
	for (int i = 0; i<TABLE_SIZE; i++)
	{
		data.sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * 3.14 * 2.);
	}
	

	err = Pa_OpenDefaultStream(&stream,
		0,          /* no input channels */
		2,          /* stereo output */
		paFloat32,  /* 32 bit floating point output */
		SAMPLE_RATE,
		paClipOff,        /* frames per buffer, i.e. the number
											 of sample frames that PortAudio will
											 request from the callback. Many apps
											 may want to use
											 paFramesPerBufferUnspecified, which
											 tells PortAudio to pick the best,
											 possibly changing, buffer size.*/
		patestCallback, /* this is your callback function */
		&data); /*This is a pointer that will be passed to
				your callback*/

	err = Pa_StartStream(stream);
	std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
	Pa_Sleep(unit);

	err = Pa_StopStream(stream);
}
void menu() {
	system("cls");
	cout << "================Morse-Code-Generator====================" << "\n";
	cout << "1) Run Program " << "\n";
	cout << "2) Exit" << "\n";
}

void run() {
	PaError err;
	string inputbuffer;
	int wpm = 5;
	float unit = 0;
	int unitmili = 0;
	bool validInput = false;
	err = Pa_Initialize();
	system("cls");
	while (validInput == false) {

		cout << "How many words a minuite? " << "\n";
		cin >> inputbuffer;
		cin.clear();
		cin.ignore();
		wpm = atoi(inputbuffer.c_str());
		if (wpm > 0 && wpm <= 26) {
			validInput = true;
			cin.clear();
			
			cout << "Please enter a String" << "\n";
			getline(cin, inputbuffer);
			unit = 1.2f / wpm;
			unitmili = unit * 1000;
			if (validInput == true)
			{
				for (int i = 0; i < inputbuffer.size();i++) {
					inputbuffer.at(i);
					if ('A' == inputbuffer.at(i) || 'a' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('B' == inputbuffer.at(i) || 'b' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('C' == inputbuffer.at(i) || 'c' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('D' == inputbuffer.at(i) || 'd' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('E' == inputbuffer.at(i) || 'e' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('F' == inputbuffer.at(i) || 'f' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('G' == inputbuffer.at(i) || 'g' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('H' == inputbuffer.at(i) || 'h' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('I' == inputbuffer.at(i) || 'i' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('J' == inputbuffer.at(i) || 'j' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('K' == inputbuffer.at(i) || 'k' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('L' == inputbuffer.at(i) || 'l' == inputbuffer.at(i)) {
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('M' == inputbuffer.at(i) || 'm' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('O' == inputbuffer.at(i) || 'o' == inputbuffer.at(i)) {
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('P' == inputbuffer.at(i) || 'p' == inputbuffer.at(i)) {
						tone(unit); //dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('Q' == inputbuffer.at(i) || 'q' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit); //dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('R' == inputbuffer.at(i) || 'r' == inputbuffer.at(i)) {
						tone(unit); //dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit); //dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('S' == inputbuffer.at(i) || 's' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('T' == inputbuffer.at(i) || 't' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('U' == inputbuffer.at(i) || 'u' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('V' == inputbuffer.at(i) || 'v' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('W' == inputbuffer.at(i) || 'w' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('X' == inputbuffer.at(i) || 'x' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('Y' == inputbuffer.at(i) || 'y' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('Z' == inputbuffer.at(i) || 'z' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('1' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('2' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('3' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('4' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('5' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('6' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('7' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('8' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('9' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('0' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if (' ' == inputbuffer.at(i)) {
						cout << "space";
						int temp1 = 0;
						int temp2 = 0;
						temp1 = unitmili * 3;
						temp2 = unitmili * 7;
						std::this_thread::sleep_for(std::chrono::milliseconds(temp2 - temp1));
					}
					else if ('.' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if (',' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if (':' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
					}
					else if ('-' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('\'' == inputbuffer.at(i)) {
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('/' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
					else if ('=' == inputbuffer.at(i)) {
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit);//dit
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili));
						tone(unit * 3);//dah
						std::this_thread::sleep_for(std::chrono::milliseconds(unitmili * 3));
					}
				}
			}

		}
		else {
			cout << "Error please enter a numeric value between 0 and 25" << "\n";
		}
	}

	err = Pa_Terminate();
}
int main() {
	int input;
	bool runing = true;
	
	while (runing == true) {
		input = NULL;
		
		menu();
		
		cin.clear();
		cout << "Please enter your choice in Numeric values: ";
		cin >> input;
		cin.clear();
		cin.ignore();
		if (input == 1) {
			run();
		}
		else if(input == 2) {
			runing = false;
		}
	}
	return 0;
}

