{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
    libevdev
    pkg-config
  ];
  shellHook = ''
    echo 'clang' > .ccls
    pkg-config --cflags libevdev >> .ccls
    pkg-config --libs libevdev >> .ccls
  '';
}
