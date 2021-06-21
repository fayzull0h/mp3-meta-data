#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

void addArtist(string artist, string& command) {
	command = command + "-metadata artist=\"" + artist + "\" ";
}

void addAlbum(string album, string& command) {
	command = command + "-metadata album=\"" + album + "\" ";
}

void addOutput(string output, string& command) {
	command = command + output;
}

void addTitle(string title, string& command) {
	command = command + "-metadata title=\"" + title + "\" ";
}

void addDate(string date, string& command) {
	command = command + "-metadata date=\"" + date + "\" ";
}

void setAlbum();

int main (int argc, char *argv[]) {
	// Detect Errors
	if (argc != 2) {
		cout << "Usage: mtdata [options] [filename]\n";
		cout << "Use --album to add artist, album, date to multiple files\n";
		return 0;
	}
	
	// Check for --album tag
	string albinput = "--album";
	string argument2 = argv[1];

	if (argument2 == albinput) {
		setAlbum();
		return 0;
	}

	string filename = argv[1];
	
	// Initialize ffmpeg command
	string str = "ffmpeg -i in.mp3 ";

	// Change the name of the input file to in.mp3
	// because ffmpeg creates a new file from the old file
	string _mkbuffer = "mv ";
	_mkbuffer = _mkbuffer + filename + " in.mp3";
	const char *mkBuffer = _mkbuffer.c_str();
	system(mkBuffer);

	// Make variables for metadata
	char album[50];
	char artist[50];
	char title[50];
	char date[5];
	cout << "Enter artist: ";
	cin.getline(artist, sizeof(artist));
	cout << "Enter album: ";
	cin.getline(album, sizeof(album));
	cout << "Enter title: ";
	cin.getline(title, sizeof(title));
	cout << "Enter date: ";
	cin.getline(date, sizeof(date));

	// Add metadata to ffmpeg command	
	addArtist(artist, str);
	addAlbum(album, str);	
	addTitle(title, str);
	addDate(date, str);
	addOutput(filename, str);

	// Convert to c_str and execute ffmpeg command
	const char *command = str.c_str();
	system(command);
	
	// Clean up
	system("rm in.mp3");

	return 0;	
}

void setAlbum() {
	// Create metadata holders
	vector<string> files;
	char album[50];
	char artist[50];
	char date[5];

	// Find out how many songs are in the album
	int numTracks;
	cout << "How many tracks are there in this album? ";
	cin >> numTracks;
	getchar();

	// Get the names for the files
	// and add them to the list of files
	string buffer;
	char fileNameBuffer[50];
	for (int i = 0; i < numTracks; i++) {
		cout << "Enter file name: ";
		cin.getline(fileNameBuffer, sizeof(fileNameBuffer));
		buffer = fileNameBuffer;
		files.push_back(buffer);
	}
	cout << endl;

	// Acquire metadata
	cout << "Enter album name: ";
	cin.getline(album, sizeof(album));
	cout << "Enter artist: ";
	cin.getline(artist, sizeof(artist));
	cout << "Enter date: ";
	cin.getline(date, sizeof(date));

	cout << "\nThese are the files you entered:\n";
	for (int i = 0, c = files.size(); i < c; i++) {
		cout << files[i] << endl;
	}

	cout << "\nArtist: " << artist << endl;
	cout << "Album: " << album << endl;
	cout << "Date: " << date << endl << endl;

	cout << "Does this look right? (Y/n) ";
	char confirm[2];
	cin.getline(confirm, 2);

	if (confirm == "n") {
		cout << "Ok, run this program again then.\n";
		return;
	}

	// Rename the files to inX.mp3 where X is a number
	string _mkbuffer = "mv \"";

	cout << endl;
	for (int i = 0; i < numTracks; i++) {
		_mkbuffer = _mkbuffer + files[i] + "\" in" + to_string(i) + ".mp3";
		cout << _mkbuffer << endl;
		const char *mkBuffer = _mkbuffer.c_str();
		system(mkBuffer);
		_mkbuffer = "mv \"";
	}

	// Make list of ffmpeg commands to actually change the metadata
	vector<string> commands;
	
	string command = "ffmpeg -i in";

	addAlbum(album, command);
	addArtist(artist, command);
	addDate(date, command);

	cout << endl;
	for (int i = 0; i < numTracks; i++) {
		string _temp = command;
		_temp.insert(12, to_string(i) + ".mp3 ");
		_temp = _temp + "\"" + files[i] + "\"";
		cout << _temp << endl;
		system(_temp.c_str());
	}

	// Clean up
	for (int i = 0; i < numTracks; i++) {
		string remove = "rm in" + to_string(i) + ".mp3";
		system(remove.c_str());
	}
}
