#!/usr/bin/env python3

import os
from datetime import datetime

def get_formatted_datetime():
    # Get the current date and time
    now = datetime.now()
    # Format the date and time
    formatted_datetime = now.strftime("%Y-%m-%d %H:%M:%S")
    return formatted_datetime


shader_files = os.listdir("./Shaders")

shaders = []
for shader in shader_files:
    shader_cpp_name = "_".join(shader.upper().split(".")[:-1])

    with open(f"./Shaders/{shader}", "r") as f:
        shaders.append(
            {
                "filename": shader,
                "codename": shader_cpp_name,
                "content": f.read(),
            }
        )


shader_file_content = ""

shader_file_content += "/* --------------------------------------------------------------------------------- */\n"
shader_file_content += f"/* Generated at {get_formatted_datetime()}                                                  */\n"
shader_file_content += "/* ---------------------------------                                                 */\n"
shader_file_content += "/* THIS FILE IS GENERATED USING A GENERATOR SCRIPT. DO NOT MODIFY THIS FILE DIRECTLY */\n"
shader_file_content += "/* --------------------------------------------------------------------------------- */\n\n"
shader_file_content += "#pragma once\n"


for shader in shaders:
    shader_file_content += "\n"
    shader_file_content += f"// Shaders/{shader['filename']}\n"
    shader_file_content += (
        f'const char* STEVE_SHADER_SOURCE_{shader['codename']} = R"({shader['content']})";\n'
    )


with open("./Source/Steve/Core/Shaders.hpp", "w") as f:
    f.write(shader_file_content)
