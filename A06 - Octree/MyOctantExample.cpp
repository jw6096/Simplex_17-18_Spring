#include "MyOctantExample.h"
using namespace Simplex;

Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	static uint m_uOctantCount = 1;
	static uint m_uMaxLevel = a_nMaxLevel;
	static uint m_uIdealEntityCount = a_nIdealEntityCount;
	m_pMeshMngr = m_pMeshMngr->GetInstance();
	m_pEntityMngr = m_pEntityMngr->GetInstance();

	for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().x < m_v3Min.x)
			m_v3Min.x = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().x;
		
		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().x > m_v3Max.x)
			m_v3Max.x = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().x;

		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().y < m_v3Min.y)
			m_v3Min.y = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().y;

		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().y > m_v3Max.y)
			m_v3Max.y = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().y;

		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().z < m_v3Min.z)
			m_v3Min.z = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().z;

		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().z > m_v3Max.z)
			m_v3Max.z = m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().z;
	}

	m_v3Center = vector3((float)((m_v3Max.x + m_v3Min.x) / 2), (float)((m_v3Max.y + m_v3Min.y) / 2), (float)((m_v3Max.z + m_v3Min.z) / 2));
	std::cout << m_v3Center.x << "," << m_v3Center.y << "," << m_v3Center.z << std::endl;
}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	m_pMeshMngr = m_pMeshMngr->GetInstance();
	m_pEntityMngr = m_pEntityMngr->GetInstance();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;
}

void Simplex::MyOctant::Swap(MyOctant & other)
{

}

float Simplex::MyOctant::GetSize(void)
{
	return m_fSize;
}

vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return m_v3Center;
}

vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return m_v3Min;
}

vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return m_v3Max;
}

bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{
	return false;
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
	
}

void Simplex::MyOctant::Display(vector3 a_v3Color)
{
	vector3 center = GetCenterGlobal();
	matrix4 octants = glm::scale(vector3(glm::abs(m_v3Max.x) + glm::abs(m_v3Min.x), glm::abs(m_v3Max.y) + glm::abs(m_v3Min.y), glm::abs(m_v3Max.z) + glm::abs(m_v3Min.z)));
	m_pMeshMngr->AddWireCubeToRenderList(octants, a_v3Color);
}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{

}

void Simplex::MyOctant::ClearEntityList(void)
{
	m_EntityList.clear();
}

void Simplex::MyOctant::Subdivide(void)
{
	MyOctant * subOctant = new MyOctant(m_v3Center, m_fSize);
}

MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	return m_pChild[a_nChild];
}

MyOctant * Simplex::MyOctant::GetParent(void)
{
	return m_pParent;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	return false;
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	return false;
}

void Simplex::MyOctant::KillBranches(void)
{
}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
}

uint Simplex::MyOctant::GetOctantCount(void)
{
	return uint();
}
