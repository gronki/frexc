
// #define NOT_LIL_ENDIAN

#include <iostream>
#include <fstream>
#include <png.h>

#include <renderer.hpp>
#include <space.hpp>
#include <args.hpp>
#include <lexcast.hpp>

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#define CHECK_ARG(param,type,var) if(pr.contains_key(param)) { \
	var = lexical_cast <type> (pr.get_value (param)); \
	}
	


using namespace std;

void data_write (png_structp png_ptr, png_bytep data, png_size_t length);
void data_flush (png_structp png_ptr);
int writePNG (const string& filename, int* data, int W, int H);
void print_info ();
int parse_color (const string& s);
ofstream out;


string color_table_str[] = { "red", "green", "blue", "black", "white", "cyan", "magenta", "yellow",
	"orange" };
int color_table_clr[] = { BGR(0xFF0000), BGR (0x00FF00), BGR (0x0000FF), 0, 0xFFFFFF,
	BGR(0xFF00FF), BGR(0x00FFFF), BGR (0xFFFF00), BGR(0xFF8000) };
const int color_table_num = 9;





int main (int argc, char** argv) {

	int width = 400, height = 300, iters = 200, sampling = 2;
	double fov = 3, cx = 0, cy = 0, x0 = 0, y0 = 0;
	int color0 = 0, color1 = 0, color2 = 0xFFFFFF;
	bool use_color0 = false, julia = false;
	string filename;
	
	ArgumentsParser pr;
	pr.parse (argc, argv);
	
	if (pr.contains_key ("info")) {
		print_info ();
		return 0;
	}
	
	if (pr.contains_key ("o")) {
		filename = pr.get_value ("o");
	} else {
		cout << "frexc: Brak nazwy pliku wyjscia. Wpisz 'frexc -info' by uzyskac informacje." << endl;
		return -1;
	}
	
	CHECK_ARG("w", int, width)
	CHECK_ARG("h", int, height)
	CHECK_ARG("n", int, iters);
	CHECK_ARG("s", int, sampling);
	CHECK_ARG("v", double, fov);
	CHECK_ARG("cx", double, cx);
	CHECK_ARG("cy", double, cy);
	CHECK_ARG("x0", double, x0);
	CHECK_ARG("y0", double, y0);
	
	if (pr.contains_key ("c0")) {
		use_color0 = true;
		color0 = parse_color (pr.get_value ("c0"));
	}
	
	if (pr.contains_key ("c1")) {
		color1 = parse_color (pr.get_value ("c1"));
	}
	
	if (pr.contains_key ("c2")) {
		color2 = parse_color (pr.get_value ("c2"));
	}
	
	Space s (width, height, cx, cy, fov);
	FractalRenderer* rend;
	if (pr.contains_key ("julia")) {
		if (pr.contains_key ("dist")) {
			rend = new JuliaRendererDist (x0, y0, iters);
		} else {
			rend = new JuliaRenderer (x0, y0, iters);
		}
	} else {
		if (pr.contains_key ("dist")) {
			rend = new MandelbrotRendererDist (x0,y0,iters); 
		} else {
			rend = new MandelbrotRenderer (x0,y0,iters);
		}
	}
	
	rend -> color_fractal = use_color0;
	rend -> color0 = color0;
	rend -> color1 = color1;
	rend -> color2 = color2;
	int* data = rend -> render (new int[width*height], s, sampling);
	writePNG (filename, data, width, height);
	delete[] data;
	delete rend;
	

	
	return 0;
}

void print_info () {
	cout << "frexc by gronki" << endl
		 << "\t-julia\tfraktal Julii" << endl
		 << "\t-dist\twyswietla fraktal wg. koncowej odleglosci od srodka" << endl
		 << "\t-w liczba\twysokosc" << endl
		 << "\t-h liczba\tszerokosc" << endl
		 << "\t-v liczba\tszerokosc wziernika" << endl
		 << "\t-cx liczba\tsrodek widoku - X" << endl
		 << "\t-cy liczba\tsrodek widoku - Y" << endl
		 << "(M - fraktal Mandelbrota, J - fraktal Julii)" << endl
		 << "\t-x0 liczba\tparametr a (J), odcieta punktu startowego (M)" << endl
		 << "\t-y0 liczba\tparametr b (J), rzedna punktu startowego (M)" << endl
		 << "\t-n liczba\tliczba iteracji" << endl
		 << "\t-c0 kolor\tkolor fraktala (np. green lub F0A73B)" << endl
		 << "\t-c1 kolor\tkolor galezi (jw)" << endl
		 << "\t-c2 kolor\tkolor tla (jw)" << endl
		 << "\t-s liczba\tpierwiastek z liczby probek" << endl << endl;
		 
	cout << "Dostepne etykietki kolorow:" << endl;
		 
	for (int i = 0; i < color_table_num; ++i) 
		cout << color_table_str[i] << " (" << hex << BGR(color_table_clr[i]) << ")   ";
		
	cout << endl << png_get_copyright(NULL) << endl;
}

int writePNG (const string& filename, int* data, int W, int H) {
	
	
	png_structp png_ptr = png_create_write_struct
		(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		return -1;
	}
	
	png_infop info_ptr = png_create_info_struct (png_ptr);
	
	png_set_IHDR (png_ptr, info_ptr, W, H, 8,
		PNG_COLOR_TYPE_RGB,PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	
	png_set_write_fn (png_ptr, png_get_io_ptr (png_ptr),
		data_write, data_flush);	

	out.open (filename.c_str(), ios::binary);
	
	if (!out) {
		return -1;
	}
	
	png_bytep* rows = new png_bytep[H];
	png_bytep datap = (png_bytep) data;
	int* p; int x;
	for (int y = 0; y < H; ++y) {
		rows[y] = (png_bytep)(datap + 4*W*y);
		for (x = 0, p = (int*)rows[y]; x < W; ++x) *(p++)<<=8;
	}
	
	png_set_rows (png_ptr, info_ptr, rows);
	
	png_write_png (png_ptr, info_ptr, 
		 PNG_TRANSFORM_STRIP_FILLER, //PNG_TRANSFORM_IDENTITY,
		NULL);
		
	png_destroy_write_struct(&png_ptr, &info_ptr);	
	
	delete[] rows;
	
	return 0;
}

void data_write (png_structp png_ptr, png_bytep data, png_size_t length) {
	try {
		out.write ((char*)data, length);
	} catch (...) {}
}

void data_flush (png_structp png_ptr) {
	try {
	out.flush ();
	} catch (...) {}
}

int parse_color (const string& s) {

	for (int i = 0; i < color_table_num; ++i) 
		if (s == color_table_str[i]) 
			return color_table_clr[i]; 
		
		
	stringstream ss;
	int clr;
	
	ss << s;
	ss >> hex >> clr;
	
	return BGR(clr);
}
