{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    gnumake
    libevdev
    pkg-config
    python3
  ];
  propagatedBuildInputs = with pkgs; [
    libevdev
  ];
  shellHook = ''
    echo 'clang' > .ccls
    pkg-config --cflags libevdev >> .ccls
    pkg-config --libs libevdev >> .ccls
  '';
}
