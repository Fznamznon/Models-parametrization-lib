#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>

int main(int, char *[]) {
  std::string inputFilename = "heart.vtk";

 // Get all data from the file
  vtkSmartPointer<vtkUnstructuredGridReader> reader =
      vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // vtkSmartPointer<vtkUnstructuredGrid> heart  = vtkSmartPointer<vtkUnstructuredGrid>::NewInstance(reader->GetOutput());


 //Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
  //     vtkSmartPointer<vtkPolyDataMapper>::New();
  // sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  // vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
  // sphereActor->SetMapper(sphereMapper);

  // vtkSmartPointer<vtkConeSource> coneSource =
  //     vtkSmartPointer<vtkConeSource>::New();

  // vtkSmartPointer<vtkPolyDataMapper> coneMapper =
  //     vtkSmartPointer<vtkPolyDataMapper>::New();
  // coneMapper->SetInputConnection(coneSource->GetOutputPort());

  // vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
  // coneActor->SetMapper(coneMapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // renderer->AddActor(sphereActor);
  // renderer->AddActor(coneActor);
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
