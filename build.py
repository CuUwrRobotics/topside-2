#!/usr/bin/env python3

import logging
import subprocess
import os

def build_topside() -> bool:
    # Configure build
    currentDirectory = os.getcwd()

    logging.info(f"[Topside] Setting working dir to {currentDirectory}/lib/navigator-lib")
    os.chdir(currentDirectory + "/lib/navigator-lib")

    logging.info("[Topside] Building navigator-lib")
    cargo = subprocess.run(["cargo", "build"], capture_output=True)
    logging.info("[Topside] Successfully built navigator-lib!")

    if (cargo.returncode != os.EX_OK):
        logging.error("[Topside] Failed to build navigator-lib")
        print(cargo.stderr)
        return False

    logging.info(f"[Topside] Setting working dir to {currentDirectory}")
    os.chdir(currentDirectory)

    logging.info("[Topside] Configuring CMake build for topside")
    cmake_configure = subprocess.run(["cmake", "-B", "build", "-G", "Ninja"], capture_output=True)
    logging.info("[Topside] Successfully configured CMake!")

    if (cmake_configure.returncode != os.EX_OK):
        logging.error("[Topside] Failed to configure CMake")
        print(cmake_configure.stderr)
        return False

    logging.info("[Topside] Building CMake target: topside")
    cmake_build = subprocess.run(["cmake", "--build", "build", "--target", "topside"], capture_output=True)
    logging.info("[Topside] Successfully built target: topside!")

    if (cmake_build.returncode != os.EX_OK):
        logging.error("[Topside] Failed to build target: topside")
        print(cmake_build.stderr)
        return False

    return True

def build_rov() -> bool:
    return False

def main():
    logging.basicConfig(
        level=logging.INFO,
        format="[%(asctime)s.%(msecs)03d] [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S"
)

    logging.info('Building topside')
    if not build_topside():
        logging.error('Failed to build topside. Terminating build')

    logging.info('Building rov')
    if not build_rov():
        logging.error('Failed to build rov. Terminating build')


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("KeyboardInterrupt received. Terminating build")
