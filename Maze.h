#pragma once
#include "RenderedObject.h"
using namespace std;

class Maze :
    public RenderedObject
{
public:
	Maze(string filename);

	// Inherited via RenderedObject
	virtual void InitializeDeviceDependent(ID3D11Device1*) override;

	virtual void Reset() override;

	virtual void Render(DirectX::SpriteBatch*) override;


private:
	struct MazeLine {
		union {
			struct {
				int Row;
				int ColumnStart, ColumnEnd;
			};
			struct {
				int Column;
				int RowStart, RowEnd;
			};
		};
	};

	list<MazeLine> _verticalLines;    // Vertical lines in the maze
	list<MazeLine> _horizontalLines;    // Horizontal lines in the maze
	list<POINT> _deployPoints;

	char _name[200];
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _texture;

	void ReadHorizontalLines(fstream& mazeLayout);
	void ReadVerticalLines(fstream& mazeLayout);
};

