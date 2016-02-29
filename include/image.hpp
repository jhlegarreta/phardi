#ifndef IMAGE_H
#define IMAGE_H

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkOrientImageFilter.h>
#include <itkNiftiImageIO.h>
#include <itkGDCMImageIO.h>
#include <itkRGBAPixel.h>

namespace pfiber {

    typedef float                       PixelType;
    typedef itk::Image< PixelType, 2 >  Image2DType;
    typedef itk::Image< PixelType, 3 >  Image3DType;
    typedef itk::Image< PixelType, 4 >  Image4DType;
    
    typedef itk::NiftiImageIO           NiftiType;
    typedef itk::GDCMImageIO            DicomType;

    typedef Image2DType::IndexType      Index2DType;
    typedef Image2DType::SizeType       Size2DType;
    typedef Image2DType::RegionType     Region2DType;
    typedef Image2DType::SpacingType    Spacing2DType;
    typedef Image2DType::PointType      Origin2DType;
    typedef Image2DType::DirectionType  Direction2DType;

    typedef Image3DType::IndexType      Index3DType;
    typedef Image3DType::SizeType       Size3DType;
    typedef Image3DType::RegionType     Region3DType;
    typedef Image3DType::SpacingType    Spacing3DType;
    typedef Image3DType::PointType      Origin3DType;
    typedef Image3DType::DirectionType  Direction3DType;
  
    typedef Image4DType::IndexType      Index4DType;
    typedef Image4DType::SizeType       Size4DType;
    typedef Image4DType::SpacingType    Spacing4DType;
    typedef Image4DType::PointType      Origin4DType;
    typedef Image4DType::DirectionType  Direction4DType;

    
    itk::ImageIOBase::Pointer getImageIO(std::string input){
        itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO(input.c_str(), itk::ImageIOFactory::ReadMode);

        imageIO->SetFileName(input);
        imageIO->ReadImageInformation();

        return imageIO;
    }

    itk::ImageIOBase::IOComponentType component_type(itk::ImageIOBase::Pointer imageIO){
        return imageIO->GetComponentType();
    }

    itk::ImageIOBase::IOPixelType pixel_type(itk::ImageIOBase::Pointer imageIO){
        return imageIO->GetPixelType();
    }

    size_t num_dimensions(itk::ImageIOBase::Pointer imageIO){
        return imageIO->GetNumberOfDimensions();
    }    

   template<typename TImageType>
   void ReadImage(std::string filename, typename TImageType::Pointer image)
   {
        typedef itk::ImageFileReader<TImageType> ReaderType;
        typename ReaderType::Pointer reader = ReaderType::New();
 
        reader->SetFileName(filename);
 
        try {
            reader->Update();
        } catch (itk::ExceptionObject &err) {
            LOG_ERROR << "ExceptionObject caught !";
            std::cerr <<  err << std::endl;
            std::cerr << "Error reading file " << filename << std::endl;
            
        }
        image->Graft(reader->GetOutput());
    }

    template<typename TImageType>
    void CreateImage(typename TImageType::Pointer image, 
                     typename TImageType::SizeType size, 
                     typename TImageType::IndexType index, 
                     typename TImageType::SpacingType spacing, 
                     typename TImageType::PointType origin,
                     typename TImageType::DirectionType direction){
        using namespace itk;

        typename TImageType::RegionType region;

        region.SetSize(size);
        region.SetIndex(index);
        image->SetRegions(region);
        image->SetSpacing(spacing);
        image->SetOrigin(origin);
        image->SetDirection(direction);
        image->Allocate();

    }

    template<typename TImageType, typename TImageIO>
    void WriteImage(std::string filename,  typename TImageType::Pointer image){
        using namespace itk;
        
        typename TImageIO::Pointer nifti_io = TImageIO::New();
        nifti_io->SetPixelType(itk::ImageIOBase::SCALAR);
        nifti_io->SetComponentType(itk::ImageIOBase::FLOAT);
       
        typename itk::ImageFileWriter<TImageType>::Pointer dwi_writer = itk::ImageFileWriter<TImageType>::New();
        dwi_writer->SetFileName(filename);
        dwi_writer->SetInput(image);
        dwi_writer->SetImageIO(nifti_io);
        try {
            dwi_writer->Update();
        } catch (itk::ExceptionObject &err) {
            LOG_ERROR << "ExceptionObject caught !";
            std::cerr << err << std::endl;            
            std::cerr << "Error writting file " << filename  << std::endl;
        }
    }
}

#endif

