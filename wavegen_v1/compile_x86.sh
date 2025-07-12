#!/bin/bash

set -e

# Path to your Qt6 installation
QT_PATH="$HOME/Qt/6.5.3/gcc_64"

# Required Qt components
REQUIRED_MODULES=(
    "$QT_PATH/lib/cmake/Qt6Widgets/Qt6WidgetsConfig.cmake"
        "$QT_PATH/lib/cmake/Qt6WidgetsTools/Qt6WidgetsToolsConfig.cmake"
	    "$QT_PATH/lib/cmake/Qt6CoreTools/Qt6CoreToolsConfig.cmake"
    )

    echo "🔍 Checking Qt6 modules in: $QT_PATH"

    missing_modules=0
    for module in "${REQUIRED_MODULES[@]}"; do
	        if [ ! -f "$module" ]; then
			        echo "❌ Missing: $module"
				        missing_modules=1
					    else
						            echo " Found: $module"
							        fi
							done

							if [ $missing_modules -ne 0 ]; then
								    echo -e "\nQt6 installation is incomplete!"
								        echo "Run: ~/Qt/MaintenanceTool"
									    echo "   → Add or remove components → Select Qt 6.5.3 → Add:"
									        echo "      - Qt Widgets"
										    echo "      - Qt Core Tools"
										        echo "      - Qt Widgets Tools"
											    exit 1
							fi

							# Build setup
							BUILD_DIR="build_x86"
							echo -e "\nCreating build directory: $BUILD_DIR"
							rm -rf $BUILD_DIR
							mkdir $BUILD_DIR && cd $BUILD_DIR

							echo -e "\nRunning cmake..."
							cmake .. -DCMAKE_PREFIX_PATH=$QT_PATH

							echo -e "\nBuilding..."
							make -j$(nproc)

							echo -e "\n Build complete!"

