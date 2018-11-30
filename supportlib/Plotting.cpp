//
// Created by ktulhu on 24/11/2018.
//

#include <Plotting.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1F.h>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
struct Plot {
    Plot(XYData* fd)
        :   title{"Graph"},
            xlabel{""},
            ylabel{""} {
        x = fd->x.data();
        y = fd->y.data();
        n = fd->x.size();
    }
    virtual ~Plot() {
    }

    void make_plot(const std::string& save_path) {
        std::stringstream ss;
        ss << title << ";" << xlabel << ";" << ylabel;
        TGraph *graph = new TGraph(n, x, y);
        graph->SetTitle(ss.str().c_str());

        TCanvas c;
        graph->Draw();
        c.Print(save_path.c_str());
        delete graph;
    }

    T *x, *y;
    int n;
    std::string title, xlabel, ylabel;
};

void grph::plot_file(const std::string &path, const std::string &save_path) {
    FileParse fp{path};
    auto data = fp.parse();
    Plot<double> p{data.get()};
    p.title = fp.title;
    p.xlabel = fp.xlabel;
    p.ylabel = fp.ylabel;
    std::cout << "Plotting data @ " << data.get() << " as '" << save_path << "'." << std::endl;
    p.make_plot(save_path);
}

void grph::plot_XY_data(XYData *fd, const std::string &save_path) {
    Plot<double> p{fd};
	std::cout << "Plotting data @ " << fd << " as '" << save_path << "'." << std::endl;
    p.make_plot(save_path);
}

void grph::plot_XY_data(XYData *fd, const std::string &title, const std::string &save_path) {
    Plot<double> p{fd};
    p.title = title;
	std::cout << "Plotting data @ " << fd << " as '" << save_path << "'." << std::endl;
    p.make_plot(save_path);
}

void grph::plot_XY_data(XYData *fd, const std::string &title, const std::string &xlabel, const std::string &ylabel,
                        const std::string &save_path) {
    Plot<double> p{fd};
    p.title = title;
    p.xlabel = xlabel;
    p.ylabel = ylabel;
	std::cout << "Plotting data @ " << fd << " as '" << save_path << "'." << std::endl;
    p.make_plot(save_path);
}

void grph::plot_histogram(const std::vector<double> & v, const std::string& save_path) {
	double maximum = 1.5e4;
	TH1F* h_Uniform = new TH1F("values", "random numbers",  100,  0, maximum);

	for (int i = 0; i < v.size(); ++i) {
		h_Uniform->Fill(v.at(i));
	}

	h_Uniform->SetMinimum(0);
	TCanvas canvas;
	h_Uniform->Draw();
	canvas.Print(save_path.c_str());
	delete h_Uniform;
}
