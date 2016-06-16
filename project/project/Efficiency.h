/**
 * Defines how efficiency is counted.
 * By MOKT (Max Ovsiankin, Ori Klein, Keivan Safavi, Tomer Erlich)
 */

#ifndef __EFFICIENCY_H
#define __EFFICIENCY_H

/**
 * Handles counting efficiency.
 */
namespace Efficiency {
/**
 * Keeps track of how many operations were performed on base data structures.
 */
extern int totalDataStructureOperations;
/**
 * Keeps track of how many program operations were performed.
 */
extern int totalProgramOperations;
}

#endif
