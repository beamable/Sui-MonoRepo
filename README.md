# 🧩 Cross-Platform Sui Integration – Unity • Unreal • Microservices • Wallet Integration

Welcome to the unified repository for our cross-platform SUI integration. This monorepo consolidates all major components required to integrate Sui blockchain features into both Unity and Unreal Engine projects, along with necessary microservices and wallet support.

---

## 📦 Repository Overview

---

## 🎮 Project Components

### 🧠 Unity Game Sample
- Built with Unity 6
- Beamable SDK integration for online services (auth, stats, leaderboards, etc.)
- Sui wallet support for WebGL builds via custom JavaScript bridge
- Optimized for Web, Android, and iOS platforms

### 🎬 Unreal Engine Game
- Built with Unreal Engine 5+
- Modular plugin-based architecture
- Supports Sui wallet integration via Blueprints and some C++ code

### ☁️ Microservices
- Built using .NET 6+ and Beamable Microservice SDK
- Services include:
    - Federated Authentication
    - Federated Inventory
- Deployed via Beamable CLI or Docker
- This has already been linked to both the Unity and Unreal projects

### 🔐 Wallet Integration
- Supports Sui wallet bridge (e.g. via `@mysten/wallet-standard`)
- Compatible with Unity WebGL builds using a `.jslib` plugin
- TypeScript → Webpack → UMD bundle

---