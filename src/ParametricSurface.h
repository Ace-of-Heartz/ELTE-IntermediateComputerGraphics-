//
// Created by ace on 2024.10.19..
//
#ifndef PARAMETRICSURFACES_H
#define PARAMETRICSURFACES_H

#include <glm/glm.hpp>


class ParamSurf {
public:
    [[nodiscard]] virtual glm::vec3 GetPos(float u,float v) const noexcept;
    [[nodiscard]] virtual glm::vec3 GetNorm(float u, float v) const noexcept {
        float const h = ParamSurf::GetOffset();

        glm::vec3 const du = (GetPos(u + h, v) - GetPos(u, v)) / h;
        glm::vec3 const dv = (GetPos(u, v + h) - GetPos(u, v)) / h;
        return normalize(cross(du,dv));
    }
    [[nodiscard]] virtual glm::vec2 GetTex(float u, float v) const noexcept {
        return {u,v};
    }
private:
    [[nodiscard]] virtual float GetOffset() const noexcept {
        return 0.01f;
    }

};

class Quad : public ParamSurf{
public:
    [[nodiscard]] glm::vec3 GetPos(float u,float v) const noexcept override {
        return {u,v,0.0f};
    }
    [[nodiscard]] glm::vec3 GetNorm(float u, float v) const noexcept override {
        return {0.0f,0.0f,1.0f};
    }
};

class Sphere : public ParamSurf {
public:
    [[nodiscard]] glm::vec3 GetPos( float u, float v ) const noexcept override
    {
        u = u * glm::pi<float>();

        v = glm::two_pi<float>() * v;
        return {sin(u) * cos(v),sin(u) * sin(v), cos(u)};
    }
    // [[nodiscard]] glm::vec3 GetNorm( float u, float v ) const noexcept override
    // {
    //     glm::vec3 const du = {cos(u) * cos(v), cos(u) * sin(v), -sin(u)};
    //     glm::vec3 const dv = {sin(u) * -sin(v), sin(u) * cos(v),0.f};
    //
    //     return normalize(glm::vec3(sin(u) * cos(v),sin(u) * cos(v),cos(u) ));
    // }
};

template <int N>
class Bezier : public ParamSurf {
public:
    explicit Bezier(std::array<std::array<glm::vec3,N>,N> ps) : m_ps(ps){}

    [[nodiscard]] glm::vec3 GetPos( float u, float v ) const noexcept override {

        auto res = GetCoeff(u, v);

        auto Bu = res[0];
        auto Bv = res[1];
        auto pos = glm::vec3(0.0f);
        for (int i = 0;i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                pos += m_ps[i][j] * Bu[i] * Bv[j];
            }
        }
        return pos;
    }

private:
    std::tuple<std::array<float,N>> GetCoeff(float u, float v) const{
        std::array<float,N> Bu;
        std::array<float,N> Bv;

        float nFact = 1.0f;
        for (float i = 2;i < N;++i) {
            nFact *= i;
        }
        for (int k = 0;k <= floor(N / 2.);++k) {

            float kF = k;
            float kFact1 = 1.0f;
            float kFact2 = 1.0f;
            for (float i = 2.f;i < kF;++i) {
                kFact1 *= i;

            }
            for (float i = 2.f;i <= N-kF;++i) {
                kFact2 *= i;
            }

            Bu[k] = pow(u,k) * pow((1-u),N-k) * (nFact / kFact1 / kFact2);
            Bu[N-k] = pow(u,N-k) * pow((1-u),k) * (nFact / kFact1 / kFact2);

            Bv[k] = pow(u,k) * pow(v,k) * (nFact / kFact1 / kFact2);
            Bv[N-k] = pow(u,N-k) * pow(v,k) * (nFact / kFact1 / kFact2);
        }
        return std::make_tuple(Bu,Bv);
    }

    std::array<std::array<glm::vec3,N>,N> m_ps;



};

#endif //PARAMETRICSURFACES_H
