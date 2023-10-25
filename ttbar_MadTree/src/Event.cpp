
#include "Event.hpp"
#include "Config.hpp"
#include "DelphesTree.hpp"

#include <array>
#include <iostream>

void Event::Set(Index index, float value) { m_variables[index] = value; }

float Event::Get(Index index) const
{
    if (m_variables.find(index) == m_variables.end()
        || !m_variables.at(index).has_value()) {
        std::clog << "Variable " << GetName(index)
                  << " was not found or does not contain value\n";
    }
    return m_variables.at(index).value_or(0);
}

bool Event::HasTwoMu(const DelphesTree* tree) const
{
    if (tree->Muon_size < 2) return false;
    return true;
}

bool Event::HasTwoB(const DelphesTree* tree, int& b0, int& b1) const
{
    std::array<int, 2> b;
    int                count = 0;
    for (int i = 0; i < tree->Jet_size; ++i) {
        if (tree->Jet_Flavor[i] == 5) { b[count++] = i; }
        if (count == 2) break;
    }
    if (count < 2) return false;
    b0 = b[0];
    b1 = b[1];
    return true;
}

bool Event::FindTwoTop(const DelphesTree* tree, int& t0, int& t1) const
{
    std::array<int, 2> t;
    int                count = 0;
    for (int i = 0; i < tree->Particle_size; ++i) {
        // status see https://pythia.org/latest-manual/ParticleProperties.html
        // top-quark from 22 : intermediate (intended to have preserved mass)
        // to 62 : outgoing subprocess particle with primordial kT included
        if (tree->Particle_Status[i] == 62) {
            if (tree->Particle_PID[i] == 6) {
                t[0] = i;
                ++count;
            } else if (tree->Particle_PID[i] == -6) {
                t[1] = i;
                ++count;
            }
        }
    }
    if (count < 2) return false;
    t0 = t[0];
    t1 = t[1];
    return count == 2;
}
