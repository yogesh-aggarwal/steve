#!/usr/bin/env python3

import os
from datetime import datetime


SHADERS_DIR = "assets/shaders"
SHADERS_HEADER_FILE = "source/steve/shaders.hpp"

def get_formatted_datetime():
    # Get the current date and time
    now = datetime.now()
    # Format the date and time
    formatted_datetime = now.strftime("%Y-%m-%d %H:%M:%S")
    return formatted_datetime


shader_files = os.listdir(SHADERS_DIR)

shaders = []
for shader in shader_files:
    shader_cpp_name = "_".join(shader.upper().split(".")[:-1])

    with open(f"{SHADERS_DIR}/{shader}", "r") as f:
        shaders.append(
            {
                "filename": shader,
                "codename": shader_cpp_name,
                "content": f.read(),
            }
        )


shader_file_content = ""
shader_file_content += "/* ------------------------------------------------------------------------------------------------------- */\n"
shader_file_content += "/* THIS FILE IS GENERATED USING THE `make shaders` TARGET. DO NOT MANUALLY MODIFY THIS FILE.               */\n"
shader_file_content += "/* ------------------------------------------------------------------------------------------------------- */\n"
shader_file_content += "\n"
shader_file_content += "#pragma once\n"


for shader in shaders:
    shader_file_content += "\n"
    shader_file_content += f"// {SHADERS_DIR}/{shader['filename']}\n"
    shader_file_content += (
        f'const char* STEVE_SHADER_SOURCE_{shader['codename']} = R"({shader['content']})";\n'
    )


with open(SHADERS_HEADER_FILE, "w+") as f:
    f.write(shader_file_content)
