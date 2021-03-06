/*
 * Watcher.hh
 *
 *  Created on: 2017-11-22
 *      Author: cxxjava@163.com
 */

#ifndef Watcher_HH_
#define Watcher_HH_

#include "Efc.hh"

namespace efc {
namespace ezk {

/**
 * This interface specifies the public interface an event handler class must
 * implement. A ZooKeeper client will get various events from the ZooKeeper
 * server it connects to. An application using such a client handles these
 * events by registering a callback object with the client. The callback object
 * is expected to be an instance of a class that implements Watcher interface.
 * 
 */

class WatchedEvent;

interface Watcher: virtual public EObject {

    /**
     * This interface defines the possible states an Event may represent
     */
    interface Event: virtual public EObject {
        /**
         * Enumeration of states the ZooKeeper may be at the event
         */
        enum KeeperState {
            /** Unused, this state is never generated by the server */
            Unknown = (-1),

            /** The client is in the disconnected state - it is not connected
             * to any server in the ensemble. */
            Disconnected = (0),

            /** Unused, this state is never generated by the server */
            NoSyncConnected = (1),

            /** The client is in the connected state - it is connected
             * to a server in the ensemble (one of the servers specified
             * in the host connection parameter during ZooKeeper client
             * creation). */
            SyncConnected = (3),

            /**
             * Auth failed state
             */
            AuthFailed = (4),

            /**
             * The client is connected to a read-only server, that is the
             * server which is not currently connected to the majority.
             * The only operations allowed after receiving this state is
             * read operations.
             * This state is generated for read-only clients only since
             * read/write clients aren't allowed to connect to r/o servers.
             */
            ConnectedReadOnly = (5),

            /**
              * SaslAuthenticated: used to notify clients that they are SASL-authenticated,
              * so that they can perform Zookeeper actions with their SASL-authorized permissions.
              */
            SaslAuthenticated = (6),

            /** The serving cluster has expired this session. The ZooKeeper
             * client connection (the session) is no longer valid. You must
             * create a new client connection (instantiate a new ZooKeeper
             * instance) if you with to access the ensemble. */
            Expired = (-112)
        };

        static KeeperState getKeeperStatefromInt(int intValue) {
			switch(intValue) {
				case -1: return KeeperState::Unknown;
				case 0: return KeeperState::Disconnected;
				case 1: return KeeperState::NoSyncConnected;
				case 3: return KeeperState::SyncConnected;
				case 4: return KeeperState::AuthFailed;
				case 5: return KeeperState::ConnectedReadOnly;
				case 6: return KeeperState::SaslAuthenticated;
				case -112: return KeeperState::Expired;

				default:
				throw ERuntimeException(__FILE__, __LINE__, "Invalid integer value for conversion to KeeperState");
			}
		}

        /**
         * Enumeration of types of events that may occur on the ZooKeeper
         */
        enum EventType {
            None = (-1),
            NodeCreated = (1),
            NodeDeleted = (2),
            NodeDataChanged = (3),
            NodeChildrenChanged = (4)
        };

        static EventType getEventTypefromInt(int intValue) {
			switch(intValue) {
				case -1: return EventType::None;
				case  1: return EventType::NodeCreated;
				case  2: return EventType::NodeDeleted;
				case  3: return EventType::NodeDataChanged;
				case  4: return EventType::NodeChildrenChanged;

				default:
					throw ERuntimeException(__FILE__, __LINE__, "Invalid integer value for conversion to EventType");
			}
		}
    };

    virtual void process(sp<WatchedEvent> event) = 0;
};

} /* namespace ezk */
} /* namespace efc */
#endif /* Watcher_HH_ */
