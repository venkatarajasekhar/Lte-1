/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */


#ifndef BUS_H_
#define BUS_H_

#include "NetworkNode.h"

class UserEquipment;
class Gateway;
//class ENodeB;
class PacketScheduler;
class CqiManager;

class Bus : public NetworkNode {
public:
	struct UserEquipmentRecord
	  {
		UserEquipmentRecord ();
		virtual ~UserEquipmentRecord ();
		UserEquipmentRecord (UserEquipment *UE);

		UserEquipment *m_UE;
		void SetUE (UserEquipment *UE);
        UserEquipment* GetUE (void) const;

        std::vector<int> m_cqiFeedback;
		void SetCQI (std::vector<int> cqi);
		std::vector<int> GetCQI (void) const;

		std::vector<int> m_cqiFeedback_oneago;
		void SetCQIone (std::vector<int> cqi);
		std::vector<int> GetCQIone (void) const;

		std::vector<int> m_cqiFeedback_twoago;
		void SetCQItwo (std::vector<int> cqi);
		std::vector<int> GetCQItwo (void) const;

		int m_schedulingRequest; // in bytes
		void SetSchedulingRequest (int r);
		int GetSchedulingRequest (void);

		int m_averageSchedulingGrants; // in bytes
		void UpdateSchedulingGrants (int b);
		int GetSchedulingGrants (void);

		int m_ulMcs;
		void SetUlMcs (int mcs);
		int GetUlMcs (void);

	  };

	typedef std::vector<UserEquipmentRecord*> UserEquipmentRecords;

	enum DLSchedulerType
	  {
	    DLScheduler_TYPE_MAXIMUM_THROUGHPUT,
	    DLScheduler_TYPE_PROPORTIONAL_FAIR,
	    DLScheduler_TYPE_FLS,
	    DLScheduler_TYPE_MLWDF,
	    DLScheduler_TYPE_EXP,
	    DLScheduler_LOG_RULE,
	    DLScheduler_EXP_RULE
	  };
	enum ULSchedulerType
	  {
		ULScheduler_TYPE_MAXIMUM_THROUGHPUT,
		ULScheduler_TYPE_FME
	  };

	Bus ();
	//ENodeB (int idElement, Cell *cell);
	Bus (int idElement, Cell *cell);
	//ENodeB (int idElement, Cell *cell, double posx, double posy);4/30
	Bus (int idElement, Cell *cell, NetworkNode* target, double posx, double posy);

	virtual ~Bus();

    void RegisterUserEquipment (UserEquipment *UE);
    void DeleteUserEquipment (UserEquipment *UE);
    int GetNbOfUserEquipmentRecords (void);
    void CreateUserEquipmentRecords (void);
    void DeleteUserEquipmentRecords (void);
    UserEquipmentRecords* GetUserEquipmentRecords (void);
    UserEquipmentRecord* GetUserEquipmentRecord (int idUE);

    void SetDLScheduler (DLSchedulerType type);
    PacketScheduler* GetDLScheduler (void) const;
    void SetULScheduler (ULSchedulerType type);
    //PacketScheduler* GetULScheduler (void) const;
	UplinkPacketScheduler* GetULScheduler (void) const;

    void ResourceBlocksAllocation ();
    void UplinkResourceBlockAllocation ();
    void DownlinkResourceBlokAllocation ();

	//like ue
	void SetTargetNode (NetworkNode *n);
	NetworkNode* GetTargetNode (void);

	void UpdateUserPosition (double time);

	void SetCqiManager (CqiManager *cm);
	CqiManager* GetCqiManager (void);

	//Debug
	void Print (void);

private:
	UserEquipmentRecords *m_userEquipmentRecords;
	NetworkNode* m_targetNode;
	CqiManager *m_cqiManager;
};

#endif /* BUS_H_ */
