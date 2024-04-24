FROM --platform=$BUILDPLATFORM ubuntu:latest AS builder

RUN apt update && apt install -y clang debootstrap curl lld llvm

RUN mkdir -p "$HOME/.dotnet9" "$HOME/.nuget/NuGet"; \
  curl -sSL https://dot.net/v1/dotnet-install.sh | bash /dev/stdin --quality daily --channel 9.0 --install-dir "$HOME/.dotnet9"; \
  cat > "$HOME/.nuget/NuGet/NuGet.Config" <<EOF
<?xml version="1.0" encoding="utf-8"?>
<configuration>
<packageSources>
    <add key="nuget.org" value="https://api.nuget.org/v3/index.json" protocolVersion="3" />
    <add key="dotnet9" value="https://pkgs.dev.azure.com/dnceng/public/_packaging/dotnet9/nuget/v3/index.json" />
</packageSources>
</configuration>
EOF

ENV DOTNET_NOLOGO=1
ENV ROOTFS_DIR=/crossrootfs/arm

RUN mkdir /dev/arm; \
  curl -sSL https://raw.githubusercontent.com/dotnet/arcade/main/eng/common/cross/arm/sources.list.jammy -o /dev/arm/sources.list.jammy; \
  curl -sSL https://raw.githubusercontent.com/dotnet/arcade/main/eng/common/cross/build-rootfs.sh |\
    bash /dev/stdin arm jammy llvm15 lldb15

RUN export dotnet9="$HOME/.dotnet9/dotnet"; \
  "$dotnet9" new webapiaot -n webapi1 && \
  "$dotnet9" publish webapi1 -o dist -c Release -r linux-arm -p:LinkerFlavor=lld \
    -p:ObjCopy=llvm-objcopy -p:SysRoot="$ROOTFS_DIR"
