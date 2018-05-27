#include "functions.h"

int main(int, char *[]) {
  std::string inputFilename = "heart.vtk";

 // Get all data from the file
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
      vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkUnstructuredGrid> heart =
    (reader->GetOutput());

  // vtkSmartPointer<vtkUnstructuredGridGeometryFilter> filter =
  // vtkSmartPointer<vtkUnstructuredGridGeometryFilter>::New();
  // filter->SetInputData(heart);
  // filter->SetInputConnection(reader->GetOutputPort());
  // filter->Update();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  //mapper->SetInputConnection(filter->GetOutputPort());

  vector<Basis> startBasis;
  vector<Basis> endBasis;
  bool load = readBasisFromObj("heart_start.obj", startBasis);
  if (!load)
    printf("FAIL start basis");
  load = readBasisFromObj("heart_end.obj", endBasis);
  if (!load)
    printf("FAIL end basis");

  vector<Basis> curBasis = startBasis;
  Model m = CreateModelFromVTKData(heart);

  Worker w(m, startBasis);
  w.initialize();
  w.setBasis(endBasis);
  w.transformModel();

  UpdateVTKDataFromModel(heart, w.getModel());
  mapper->SetInputData(heart);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);

  /* Setup interaction style */

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  /* end interaction setup */

  renderWindow->Render();
  renderWindowInteractor->Start();

  return 0;
}
