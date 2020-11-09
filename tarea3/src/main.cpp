#include <iostream>
/**
 * Interface del Sujeto
 */
class Sujeto {
 public:
  virtual void Request() const = 0;
};
/**
 * Implementacion de un Sujeto
 */
class RealSujeto : public Sujeto {
 public:
  void Request() const override {
    std::cout << "Procesando Solicitud\n";
  }
};
/**
 * El Proxy tambien implementara a Sujeto
 */
class Proxy : public Sujeto {
  /**
   * @var RealSujeto
   */
 private:
  RealSujeto *real_Sujeto_;

  bool VerificarAcceso() const {
    // Some real checks should go here.
    std::cout << "Verificando el Acceso.\n";
    return true;
  }
  void InicioDeSesion() const {
    std::cout << "Proxy: Inicio de Sesion.\n";
  }

  /**
   * Constructor del proxy usando un sujeto en especifico
   */
 public:
  Proxy(RealSujeto *real_Sujeto) : real_Sujeto_(new RealSujeto(*real_Sujeto)) {
  }

  ~Proxy() {
    delete real_Sujeto_;
  }
  /**
   * Manejando la solicitud de acceso con Proxy
   */
  void Request() const override {
    if (this->VerificarAcceso()) {
      this->real_Sujeto_->Request();
      this->InicioDeSesion();
    }
  }
};
/**
 * Clente
 */
void Cliente(const Sujeto &Sujeto) {
  // ...
  Sujeto.Request();
  // ...
}

int main() {
  std::cout << "Cliente: Con sujeto Real:\n";
  RealSujeto *real_Sujeto = new RealSujeto;
  Cliente(*real_Sujeto);
  std::cout << "\n";
  std::cout << "Cliente: Con Proxy:\n";
  Proxy *proxy = new Proxy(real_Sujeto);
  Cliente(*proxy);

  delete real_Sujeto;
  delete proxy;
  return 0;
}