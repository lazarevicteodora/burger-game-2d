# 🍔 Burger Game — 2D OpenGL Project

2D grafička aplikacija za prikaz stanja porudžbine u restoranu brze hrane, razvijena u C++ uz korišćenje OpenGL biblioteke (programabilni pajplajn, verzija 3+).

Projekat je realizovan u okviru kursa **Računarska grafika** na Fakultetu tehničkih nauka, Novi Sad.

---

## 📋 Opis

Aplikacija simulira proces pravljenja hamburgera u restoranu brze hrane kroz dve faze:

**Faza 1 — Pečenje pljeskavice**  
Igrač pomera živu pljeskavicu tasterima WASD i drži je na šporetu. Tokom kontakta, boja pljeskavice se postepeno menja ka smeđoj, a loading bar se puni. Kada je loading bar pun — pljeskavica je gotova.

**Faza 2 — Slaganje hamburgera**  
Na sceni se redom pojavljuju sastojci koje igrač WASD kontroliše i slaže na tanjir. Za kečap i senf koristi se flaša koja se cedi pritiskom na Space iznad tanjira. Kada se doda gornja zemička, ispisuje se **Prijatno!** i aplikacija završava.

---

## 🎮 Kontrole

| Taster | Akcija |
|--------|--------|
| `WASD` | Kretanje aktivnog elementa |
| `Space` | Cedenje kečapa / senfa |
| `Escape` | Izlaz iz aplikacije |
| Levi klik | Pokretanje igre (dugme za poručivanje) |

---

## 🛠️ Tehnologije

- C++
- OpenGL 3+ (programabilni pajplajn)
- GLFW — upravljanje prozorom i ulazom
- GLEW — OpenGL ekstenzije
- stb_image — učitavanje tekstura

---

## ✨ Implementirane tehnike

- Programiranje u šejderima (vertex + fragment shader)
- Uniforme
- Providne boje i teksture (alpha blending)
- Unos s miša i tastature
- Kursor sa nalepljenom slikom (dijagonalna spatula)
- Poluprovidna tekstura sa imenom i indeksom studenta (ugao ekrana)
- Frame limiter — 75 FPS
- Fullscreen prikaz

---

## 🚀 Pokretanje

### Preduslovi
- Visual Studio 2022
- NuGet paketi: GLFW, GLEW (automatski se preuzimaju)

### Koraci
1. Kloniraj repozitorijum
2. Otvori `.sln` fajl u Visual Studio-u
3. Build → Run (`F5`)

---
