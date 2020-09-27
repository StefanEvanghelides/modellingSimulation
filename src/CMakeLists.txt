add_library(Simulation
	
	models/galaxy.h
	models/galaxy.cpp
	models/star.h
	models/star.cpp

	octree/octree.h
	octree/octree.cpp

	simulation/simulation.h
	simulation/simulation.cpp

	utils/constants.h
	utils/coordinate.h
	utils/coordinate.cpp
)

add_executable(run main.cpp)

# Link Simulation first, then matplot!
# otherwise you will get linker errors

target_link_libraries(run LINK_PUBLIC Simulation)
target_link_libraries(run PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(run PUBLIC matplot)
