{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = [
    pkgs.meson
    pkgs.ninja
    pkgs.gcc
  ];
}
