// The author disclaims copyright to this source code.
#include "Configuration.h"

AbstractConfiguration::AbstractConfiguration() {
	itemIndex = 0;
}

AbstractConfiguration::~AbstractConfiguration() {
}

String AbstractConfiguration::getCurrentItemName() {
	return getItemNames()[itemIndex];
}

String AbstractConfiguration::getCurrentItemUnit() {
	return getItemUnits()[itemIndex];
}

long AbstractConfiguration::getCurrentItemValue() {
	return getItemValues()[itemIndex];
}

void AbstractConfiguration::changeCurrentItemValue(long deltaValue) {
	long newValue = getItemValues()[itemIndex] += deltaValue;
	if (newValue < getItemValuesMin()[itemIndex]) {
		newValue = getItemValuesMin()[itemIndex];
	} else if (newValue > getItemValuesMax()[itemIndex]) {
		newValue = getItemValuesMax()[itemIndex];
	}
	getItemValues()[itemIndex] = newValue;
}

void AbstractConfiguration::nextItemIndex() {
	if (itemIndex < (getItemCount() - 1)) {
		itemIndex++;
	}
}

void AbstractConfiguration::previousItemIndex() {
	if (itemIndex > 0) {
		itemIndex--;
	}
}

void AbstractConfiguration::lastItemIndex() {
	itemIndex = getItemCount() - 1;
}

void AbstractConfiguration::firstItemIndex() {
	itemIndex = 0;
}

CompositeConfiguration::CompositeConfiguration(AbstractConfiguration* c1,
		AbstractConfiguration* c2, AbstractConfiguration* c3,
		AbstractConfiguration* c4) :
		Configuration() {
	configuration1 = c1;
	configuration2 = c2;
	configuration3 = c3;
	configuration4 = c4;
	currentConfiguration = c1;
	currentConfiguration->firstItemIndex();
	itemIndex = 0;
}

CompositeConfiguration::~CompositeConfiguration() {
}

String CompositeConfiguration::getCurrentItemName() {
	return currentConfiguration->getCurrentItemName();
}

String CompositeConfiguration::getCurrentItemUnit() {
	return currentConfiguration->getCurrentItemUnit();
}

long CompositeConfiguration::getCurrentItemValue() {
	return currentConfiguration->getCurrentItemValue();
}

void CompositeConfiguration::changeCurrentItemValue(long deltaValue) {
	currentConfiguration->changeCurrentItemValue(deltaValue);
}

void CompositeConfiguration::nextItemIndex() {
	if (itemIndex < (currentConfiguration->getItemCount() - 1)) {
		// within current configuration
		currentConfiguration->nextItemIndex();
		itemIndex++;
	} else {
		// traverse configuration boundary
		if (currentConfiguration == configuration1) {
			currentConfiguration = configuration2;
			currentConfiguration->firstItemIndex();
			itemIndex = 0;
		} else if (currentConfiguration == configuration2) {
			currentConfiguration = configuration3;
			currentConfiguration->firstItemIndex();
			itemIndex = 0;
		} else if (currentConfiguration == configuration3) {
			currentConfiguration = configuration4;
			currentConfiguration->firstItemIndex();
			itemIndex = 0;
		} else if (currentConfiguration == configuration4) {
			// last item
		}
	}
}

void CompositeConfiguration::previousItemIndex() {
	if (itemIndex > 0) {
		// within current configuration
		currentConfiguration->previousItemIndex();
		itemIndex--;
	} else {
		// traverse configuration boundary
		if (currentConfiguration == configuration4) {
			currentConfiguration = configuration3;
			currentConfiguration->lastItemIndex();
			itemIndex = currentConfiguration->getItemCount() - 1;
		} else if (currentConfiguration == configuration3) {
			currentConfiguration = configuration2;
			currentConfiguration->lastItemIndex();
			itemIndex = currentConfiguration->getItemCount() - 1;
		} else if (currentConfiguration == configuration2) {
			currentConfiguration = configuration1;
			currentConfiguration->lastItemIndex();
			itemIndex = currentConfiguration->getItemCount() - 1;
		} else if (currentConfiguration == configuration1) {
			// first item
		}
	}
}

