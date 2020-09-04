#include "pch.h"
#include "Maze.h"
#include<iostream>
#include <fstream>
using namespace std;
using namespace DirectX;

Maze::Maze(string filename)
{
	fstream mazeLayout(filename, ios::in);
	// Check that the input stream is valid
	if (!mazeLayout.good()) {
		string message = "Could not open file :" + filename;
		throw new std::runtime_error(message);
	}

	 mazeLayout.getline( _name, 200);

	ReadHorizontalLines(mazeLayout);
	ReadVerticalLines(mazeLayout);
}

void Maze::ReadHorizontalLines(fstream& mazeLayout)
{
	long horizontalRows;
	mazeLayout >> horizontalRows;
	for (int nI = 0; nI < horizontalRows; nI++) {
		MazeLine mazeLine;
		mazeLayout >> mazeLine.Row >> mazeLine.ColumnStart >> mazeLine.ColumnEnd;
		_horizontalLines.push_back(mazeLine);
	}
}

void Maze::ReadVerticalLines(fstream& mazeLayout)
{
	long vericalRows;
	mazeLayout >> vericalRows;
	for (int nI = 0; nI < vericalRows; nI++) {
		MazeLine mazeLine;
		mazeLayout >> mazeLine.Column >> mazeLine.RowStart >> mazeLine.RowEnd;
		_verticalLines.push_back(mazeLine);
	}
}

void Maze::InitializeDeviceDependent(ID3D11Device1* device)
{
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(device, L"Assets/mazeBlock.bmp", nullptr,
			_texture.ReleaseAndGetAddressOf()));
}

void Maze::Reset()
{
	_texture.Reset();
}

void Maze::Render(DirectX::SpriteBatch* spriteBatch)
{
	auto blockWidth = 32;
	
	auto DrawVerticalLines = [this, spriteBatch, blockWidth]()
	{
		auto texture = _texture.Get();
		for (auto verticalLine : _verticalLines)
		{
			for (auto column = verticalLine.ColumnStart; column <= verticalLine.ColumnEnd; column++)
			{
				DirectX::SimpleMath::Vector2 screenPos(verticalLine.Row * blockWidth, column * blockWidth);
				spriteBatch->Draw(texture, screenPos);
			}
		}

	};

	auto DrawHorizontalLines = [this, spriteBatch, blockWidth]()
	{
		auto texture = _texture.Get();
		for (auto horizontalLine : _horizontalLines)
		{
			for (auto row = horizontalLine.RowStart; row <= horizontalLine.RowEnd; row++)
			{
				DirectX::SimpleMath::Vector2 screenPos(row * blockWidth, horizontalLine.Column * blockWidth);
				spriteBatch->Draw(texture, screenPos);
			}
		}
	};

	DrawVerticalLines();
	DrawHorizontalLines();
}


