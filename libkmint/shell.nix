{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell rec {
  buildInputs = with pkgs; [ gcc cmake SDL2 SDL2_image gtest ];
}
