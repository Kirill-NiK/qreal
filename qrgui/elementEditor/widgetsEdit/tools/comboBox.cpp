#include "comboBox.h"

using namespace qReal::widgetsEdit;

ComboBox::ComboBox(ToolController *controller)
	: Tool(new ComboBoxWidget, controller)
{
	mComboBox = dynamic_cast<ComboBoxWidget *>(widget());
	mTitle = tr("Combo Box");
	mTag = "ComboBox";
	mIcon = QIcon(":/icons/widgetsEditor/comboBox.png");
	mProxy = new ComboBoxProxy(mComboBox);
}

ComboBoxProxy::ComboBoxProxy(ComboBoxWidget *comboBox)
	: ToolProxy(comboBox), mComboBox(comboBox)
{
}

bool ComboBoxProxy::duplicatesEnabled() const
{
	return mComboBox->duplicatesEnabled();
}

bool ComboBoxProxy::isEditable() const
{
	return mComboBox->isEditable();
}

bool ComboBoxProxy::hasFrame() const
{
	return mComboBox->hasFrame();
}

int ComboBoxProxy::maxCount() const
{
	return mComboBox->maxCount();
}

int ComboBoxProxy::maxVisibleItems() const
{
	return mComboBox->maxVisibleItems();
}

int ComboBoxProxy::minimumContentsLength() const
{
	return mComboBox->minimumContentsLength();
}

QComboBox::SizeAdjustPolicy ComboBoxProxy::sizeAdjustPolicy() const
{
	return mComboBox->sizeAdjustPolicy();
}

void ComboBoxProxy::setDuplicatesEnabled(bool enabled)
{
	mComboBox->setDuplicatesEnabled(enabled);
}

void ComboBoxProxy::setEditable(bool editable)
{
	mComboBox->setEditable(editable);
}

void ComboBoxProxy::setFrame(bool hasFrame)
{
	mComboBox->setFrame(hasFrame);
}

void ComboBoxProxy::setMaxCount(int maxCount)
{
	mComboBox->setMaxCount(maxCount);
}

void ComboBoxProxy::setMaxVisibleItems(int maxVisibleItems)
{
	mComboBox->setMaxVisibleItems(maxVisibleItems);
}

void ComboBoxProxy::setMinimumContentsLength(int length)
{
	mComboBox->setMinimumContentsLength(length);
}

void ComboBoxProxy::setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy policy)
{
	mComboBox->setSizeAdjustPolicy(policy);
}

ComboBoxWidget::ComboBoxWidget()
	: QComboBox(), PropertyEditor(this)
{
	connect(this, SIGNAL(activated(int)), this, SLOT(onSelectionChanged(int)));
}

void ComboBoxWidget::onSelectionChanged(int index)
{
	if (index < enumValues().length()) {
		setValueInRepo(enumValues()[index]);
	}
}

void ComboBoxWidget::setPropertyValue(const QVariant &value)
{
	if (enumValues().contains(value.toString())) {
		setCurrentIndex(enumValues().indexOf(value.toString()));
	}
}

void ComboBoxWidget::setEnumValues(QStringList const &values)
{
	PropertyEditor::setEnumValues(values);
	clear();
	addItems(values);
}